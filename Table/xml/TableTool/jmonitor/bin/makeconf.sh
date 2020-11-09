#!/bin/bash
su mhsdm -c "java -jar jmonitor/dist/serverconf.jar serverconfig.xml serverlist.xml lauthc/gameserver.conf jmonitor/jmxports.xml 27001 29023 26"
