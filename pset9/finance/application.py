import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
# db.execute("CREATE TABLE shares (username, shares, symbol)")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    id = session['user_id']

    # gets the info from User and Shares table
    userInfo = db.execute("SELECT username, cash FROM users WHERE id = :id;", id=id)
    ownedStocks = db.execute("SELECT symbol, shares FROM stocks WHERE username = :username;", username=userInfo[0]['username'])
    userCash = usd(userInfo[0]['cash'])
    shares = "global"
    total = "global"
    stocks = []

    # loops over the stocks owned and gets the necessary info
    for owns in ownedStocks:
        dict = {}
        symbol = owns['symbol']
        shares = owns['shares']
        dict.update( {'symbol': symbol.upper()} )
        dict.update( {'shares': shares} )
        lookedUp = lookup(symbol)
        totaled = float(lookedUp['price'] * shares)
        dict.update( {'name': lookedUp['name']} )
        dict.update( {'total': usd(totaled)} )
        dict.update( {'price': usd(lookedUp['price'])} )
        stocks.append(dict)
    # Organizes the model to be shown on screen
        dict = {}
        dict.update( {'symbol': 'TOTAL CASH LEFT'} )
        dict.update( {'shares': ''} )
        dict.update( {'name': ''} )
        total = usd(float(lookedUp['price'] * shares))

    dict.update( {'total': userCash} )
    stocks.append(dict)
    return render_template("index.html", shares=shares, total=total, cash=userCash, stocks=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # loads the page
    if request.method == "GET":
        return render_template("buy.html")
    elif request.method =="POST":
        # gets the user id for the operation and queries the user information
        id = session['user_id']
        userInfo = db.execute("SELECT username, cash FROM users WHERE id=:id;", id=id)
        cash = userInfo[0]['cash']
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        lookedUp = lookup(symbol)
        # checks if symbol is valid
        if not lookedUp:
            return apology("Invalid Symbol")
        # checks if user has the necessary amount of money left
        price = int(lookedUp['price']) * shares
        if cash < price:
            return apology("Unaffordable")
        if shares < 1:
            return apology("You can't buy a negative numbers!")
        # checks if user has already bought the shares before
        result = db.execute("SELECT shares FROM stocks WHERE username = :username AND symbol = :symbol;", username=userInfo[0]['username'], symbol=symbol)
        if not result:
            db.execute("INSERT INTO stocks (username, symbol, shares) VALUES(:username, :symbol, :shares);", username=userInfo[0]['username'], symbol=symbol, shares=shares)
        else:
            resultant = int(result[0]['shares']) + shares
            db.execute("UPDATE stocks SET shares = :shares WHERE symbol = :symbol AND username = :username;", shares=resultant, symbol=symbol, username=userInfo[0]['username'])
        # updates user cash after the operation
        db.execute("UPDATE users SET cash = :cash WHERE id = :id;", cash=(cash-price), id=id)
    return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = session['user_id']
    userInfo = db.execute("SELECT username, cash FROM users WHERE id = :id;", id=id)
    username = userInfo[0]['username']
    cash = float(userInfo[0]['cash'])
    ownedStocks = db.execute("SELECT symbol, shares FROM stocks WHERE username = :username;", username=username)

    # loads the page
    if request.method == "GET":
        stocks = []

        # loops over the stocks owned and gets the necessary info
        for owns in ownedStocks:
            dict = {}
            symbol = owns['symbol']
            dict.update( {'symbol': symbol.upper()} )
            stocks.append(dict)

        # Organizes the model to be shown on screen
        dict = {}
        dict.update( {'symbol': ''} )
        stocks.append(dict)

        return render_template("sell.html", stocks=stocks)
    # if user requests the operation to SELL
    elif request.method =="POST":
        # gets form input
        symbol = request.form.get("symbol")
        sharesInputed = int(request.form.get("shares"))
        # looks up stock information
        lookedUp = lookup(symbol)
        # sets the amount of money to be returned to user
        price = (lookedUp['price']) * sharesInputed
        # gets the amount of shares the user has
        ownedStock = db.execute("SELECT shares FROM stocks WHERE username = :username AND symbol = :symbol", username=username, symbol=symbol)
        userShares = ownedStock[0]['shares']

        # checks if symbol is valid
        if not lookedUp:
            return apology("Invalid Symbol")
        # checks if user has the inputed a valid number of shares
        if sharesInputed < 1:
            return apology("You can't sell a negative number!")
        else:
            resultant = userShares - sharesInputed
            db.execute("UPDATE stocks SET shares = :shares WHERE symbol = :symbol AND username = :username;", shares=resultant, symbol=symbol, username=username)
        # updates user cash after the operation
            db.execute("UPDATE users SET cash = :cash WHERE id = :id;", cash=(cash-price), id=id)
        return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # gets inputed info
        username = request.form.get("username")
        password = request.form.get("password")
        # checks if user inputed a name and password
        if not username:
            return apology("You must provide an username!", 400)
        elif not password:
            return apology("Missing password", 400)
        # checks if both passwords match
        elif not request.form.get("confirmation"):
            return apology("Repeat your password!", 400)
        elif password != request.form.get("confirmation"):
            return apology("Password does not match", 400)
        # checks if the given name hasnt been registered
        elif db.execute("SELECT * FROM users WHERE username = :username", username = username):
            return apology("Username already exists", 400)
        # hashes the password and saves it into the db and saves the user id as session
        passwordHash = generate_password_hash(password)
        table = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username = username, hash = passwordHash)
        session["user_id"] = table
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")

    elif request.method == "POST":
        quote = lookup(request.form.get('symbol'))

        if not quote:
            return apology("Invalid symbol")

        return render_template("quoted.html", name=quote['name'], symbol=quote['symbol'], price=quote['price'])


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
