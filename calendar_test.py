"""
	Done on: 5th December, 2020 ~ Saturday_1
	LOG:
		Just a basic calendar version..
		Done till the CSS adjustments and styling..
	Need to be done:
		By now the calendar is ready but, month starts from Sunday.
		Needed to be done as flexible as calendar.calendar()
			calendar library has two ways Text way and HTML way... once look..
"""
intial_str = '''
<!DOCTYPE html>
<html>
	<head>
		<link href="styles.css" type="text/css" rel="stylesheet"> 
		</style>
	</head>
	<body>
		<table>''' + chr(13)

final_str = '''
		</table>
	</body>
</html>		
			'''
str_cells = ""
day_count = 0
#week_count=0
for day in range(0, 31):

	if day_count % 7 == 0:		# For each start of week, take as a row
		str_cells = str_cells + "		<tr>" +chr(13) + "			"

	str_cells = str_cells + "<td>" + str(day+1) + "</td>" 	 # Place the date in the cell
	

	if (day_count + 1) % 7 == 0:  # For each respective end of a week, end the row..
		str_cells = str_cells + chr(13) + "		</tr>" + chr(13)

	# if day_count%7 == 0:
	#	week_count = week_count + 1
	day_count = day_count + 1



# At the end of all the rows.. place the table end and html end tags..
str_cells = str_cells + "</table> </html>"

# Now write to a file
with open('calendar.html', 'w') as htmlFile:
	htmlFile.write(intial_str + str_cells + final_str)
print("Successfully created the Calendar in calendar.html file... Please check it out..!!")