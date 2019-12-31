<!DOCTYPE html>

<html lang="en" id="html">
<head>
    <meta charset="UTF-8">
    <title>Forms</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css">
    <link rel="stylesheet" href="stylesheet.css" media="screen">
</head>
<body>
	<div class="top_layer">
	<center>
		<table height="50px">
		<tr></tr>	
		</table>
		<h3>Survey</h3>
	</center>

	
	</div>
	<br><form id="data" class="_form_question" method="post" action="process_form.php">
		<button type="submit">Submit</button>
	<div class="form">
		<br>
		<table>
			<br>
			<tr>
				<td>
					Hello
				</td>
			</tr>
		</table>
	<br>
		<br>
		<table>-
			<tr>
				<td>
					Add Description
				</td>
			</tr>
		</table>
	</div><div class="form_question" id="email">
		<table id="information">
			<tr>
				<td>
					
					E:mail <input type="text" value="Write your email" name="email" id="email" class="Question" onchange="change_value(this)"> &nbsp;&nbsp;&nbsp;&nbsp;
					
				</td>
			</tr>
		</table>
		
		<table>

			<tr>
				<th class="input_size">
				Name: <input type="text" value="Enter Your Name" name="name" class="Question_answer" onchange="change_value(this)">
				</th>
			</tr>

		</table>
		<br>
		<br>
	</div><div class="form_question">
		
		<table id="information">
			<tr>
				<td>
					Question
				</td>
			</tr>
		
			
			<tr>
				<th class="input_size">
					<input type="text" value="Answer" name="Answer1" class="Question_answer" onchange="change_value(this)">
				</th>
			</tr>
		</table>
		<br>
		<br>
		
	</div><div class="form_question">
		
		<table id="information">
			<tr>
				<td>
					Question
				</td>
			</tr>
		
			
			<tr>
				<th class="input_size">
					<input type="text" value="Answer" name="Answer2" class="Question_answer" onchange="change_value(this)">
				</th>
			</tr>
		</table>
		<br>
		<br>
		
	</div>