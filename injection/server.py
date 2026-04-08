from flask import Flask, request, render_template_string

app = Flask(__name__)

# A simple, ugly HTML interface
HTML_TEMPLATE = '''
<!DOCTYPE html>
<html>
<head><title>System Admin Dashboard</title></head>
<body>
    <h2>Check Server Status</h2>
    <form action="/check" method="GET">
        Enter IP to Ping: <input type="text" name="ip">
        <input type="submit" value="Run Ping">
    </form>
    <hr>
    {% if result %}
    <pre>{{ result }}</pre>
    {% endif %}
</body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(HTML_TEMPLATE)

@app.route('/check')
def check():
    ip_address = request.args.get('ip', '')
    
    # THE VULNERABILITY:
    # We are taking user input and dropping it directly into a shell command string.
    # A legitimate command looks like: "ping -c 1 127.0.0.1"
    command = f"ping -c 1 {ip_address}"
    
    import subprocess
    try:
        # getoutput() runs the string through /bin/sh
        output = subprocess.getoutput(command)
    except Exception as e:
        output = str(e)
    
    return render_template_string(HTML_TEMPLATE, result=output)

if __name__ == '__main__':
    # Running on 0.0.0.0 so we can access it from the host
    app.run(host='0.0.0.0', port=8000)
