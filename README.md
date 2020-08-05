Run pingbackoff with a hostname to ping. It will ping the host once, with a timeout of 5 seconds. It will keep repeating on successful pings however it will sleep for longer and longer periods of time inbetween.

Basically, if the program returns you can send an email alert.

You can leave it running from within a daemontools service.

```console
~/bin/pingbackoff example.com
```

