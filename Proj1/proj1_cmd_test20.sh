#!/bin/sh

set -v

./cust_ports -h						# demonstrates -h option

# Text file options
./cust_ports -f CustDB20.dat -cust RS001 -info		# demos customer info [done]
./cust_ports -f CustDB20.dat -cust VG003 -info		# demos customer info [done]

./cust_ports -f CustDB20.dat -cust JBG58 -12		# demos FV projections [ADD Not found message]
./cust_ports -f CustDB20.dat -20			# demos FV projections for all [done]

./cust_ports -f CustDB20.dat -out zzz.dat		# demonstrates -out option

./cust_ports -f CustDB20.dat -rpt report2.txt		# demos -rpt option (default) [Done]
./cust_ports -f CustDB20.dat -rpt report2.txt -12	# demos -rpt option (12 years) [Done, add multi report]

./cust_ports -f CustDB20.dat << EOF			# demos -f starts interactive
q
n
EOF
