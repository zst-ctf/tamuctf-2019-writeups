import requests
import json
import sys
from tamuctf import app
from flask import Flask, render_template, request, jsonify, render_template_string

@app.route('/')
@app.route('/index')
def index():
    
    return render_template('index.html')

@app.route('/science', methods=['POST'])
def science():
    try:
        template = '''<html>
        <div style="text-align:center">
        <h3>The result of combining {{ chem1 }} and {{ chem2 }} is:</h3></br>
        <iframe src="https://giphy.com/embed/AQ2tIhLp4cBa" width="468" height="480" frameBorder="0" class="giphy-embed" allowFullScreen></iframe></div>
        </html>'''

        return render_template_string(template, 
            chem1=request.form['chem1'],
            chem2=request.form['chem2'],
            dir=dir, help=help, locals=locals)
    except:
        return "Something went wrong"


