#!/usr/bin/env python
# This is some secure program that uses security. 
import sys 
 
validPassword = 'secret' #this is our password. 
 
inputPassword = raw_input('Please Enter Password: ') 
 
if inputPassword == validPassword: 
 print 'You have access!' 
else: 
 print 'Access denied!' 
 sys.exit(0) 
 
print 'Welcome!' 
