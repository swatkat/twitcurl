#
# Regular cron jobs for the libtwitcurl package
#
0 4	* * *	root	[ -x /usr/bin/libtwitcurl_maintenance ] && /usr/bin/libtwitcurl_maintenance
