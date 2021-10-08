import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("Name")
        day = request.form.get("Day")
        month = request.form.get("Month")
        # above ⬆️ -> get the input from forms and below ⬇️ it inserts the values in the db
        table = db.execute("INSERT INTO birthdays (name, day, month) VALUES(:name, :day, :month)", name=name, day=day, month=month)

        return redirect("/")

    else:

        rows = db.execute("SELECT * from birthdays")
        return render_template("index.html", title="results", rows=rows)