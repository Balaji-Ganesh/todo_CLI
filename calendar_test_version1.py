"""
	Done on: 5th December, 2020 ~ Saturday_1
	Update LOG:
		Made sections with class as monthDay, yearDay, weekDay and Notes.
		and some formattings.
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
	</head>

	<table class="global_table">
		<tr>
				<th>Sunday</th>
				<th>Monday</th>
				<th>Tuesday</th>
				<th>Wednesday</th>
				<th>Thursday</th>
				<th>Friday</th>
				<th>Saturday</th>
		</tr>''' + chr(13)


final_str = '''
	</table>
</html>		
			'''
local_table = ''' 
				<table class='local_table'> 
					<tr>
						<td class="yearDay"> {0} </td>
						<td class="monthDay"> {1} </td>
					</tr>
					<tr>
						<td class="weekDay"> {2} </td>
						<td class="notes">Notes</td> <!-- Try a line to place here.. -->
					</tr>
				</table>''' + chr(13)

str_cells = ""
monthDay_count = 0
weekDay_count = 0
yearDay_count = 0

for day in range(0, 31+1):

	if monthDay_count % 7 == 0:		# For each start of week, take as a row
		weekDay_count = 0
		str_cells = str_cells + "		<tr>" +chr(13) + "			"

	# str_cells = str_cells + "<td>" + str(day+1) + "</td>" 	 # Place the date in the cell
	str_cells = str_cells + "<td>" + local_table.format(yearDay_count, monthDay_count, weekDay_count) + "			</td>"+chr(13) + "			"
	

	if (monthDay_count + 1) % 7 == 0:  # For each respective end of a week, end the row..
		str_cells = str_cells + chr(13) + "		</tr>" + chr(13)

	# Increment the counters...
	monthDay_count = monthDay_count + 1
	weekDay_count = weekDay_count + 1
	yearDay_count = yearDay_count + 1

# Now write to a file
with open('calendar.html', 'w') as htmlFile:
	htmlFile.write(intial_str + str_cells + final_str)
print("Successfully created the Calendar in calendar.html file... Please check it out..!!")