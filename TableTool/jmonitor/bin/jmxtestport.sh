#!/bin/bash
java -cp jmonitor/dist/serverconf.jar JMXTest service:jmx:rmi://$1:$3/jndi/rmi://$1:$2/jmxrmi
