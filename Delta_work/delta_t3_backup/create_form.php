<?php
// Initialize the session
session_start();
 
// Check if the user is logged in, if not then redirect him to login page
if(!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true){
    header("location: index.php");
    exit;
}
?>


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
		<h3>Questions</h3>
	</center>

	
	</div>
	<br>
	<form id="data" class="_form_question" method="post" action="process_form.php">
		<button type="submit">Submit</button>
	<div class="form">
		<br>
		<table>
			<br>
			<tr>
				<td>
					<input type="text" name="title" value="Untitled Form" onchange="change_value(this)">
				</td>
			</tr>
		</table>
		<br>
		<br>
		<table>
			<tr>
				<td>
					<input type="text" name="description" value="Add Description" class="description" onchange="change_value(this)">
				</td>
			</tr>
		</table>
	</div>
	
	<div class="form_question">
		<table id="information">
			<tr>
				<td>
					<span>
					<input type="text" value="Question" name="Question1" id="Question1" class="Question" onchange="change_value(this)"> &nbsp;&nbsp;&nbsp;&nbsp;
					</span>
					<span>
						<select id="selectform_add0" name="Select1" onchange="change()">
  							<option value="Text">Text</option>
						</select>
					</span>
				</td>
			</tr>
		</table>
		
		<table>

			<tr>
				<th class="input_size">
					<input type="text" value="Answer" name="Answer1" class="Question_answer" onchange="change_value(this)">
				</th>
			</tr>

		</table>
		<br>
		<br>
	</div>

	</form>
	<button onclick="addform()" class="add_option_form">Add More Questions</button>
	<button onclick="html_check()" class="add_option_form">Click</button>
<script type="text/javascript">
	var question_index = 1;
function addform() {
	question_index++;
	div_id = document.getElementById('data');
	count_number_of_child = div_id.childElementCount;
	new_question_block = document.createElement('div');
	new_question_block.setAttribute('class',"form_question");
	new_question_block.innerHTML = '<table id="information"><tr><td><span><input type="text" name="Question' + question_index + '" value="Question" id="Question1" class="Question" onchange="change_value(this)"> &nbsp;&nbsp;&nbsp;&nbsp;</span><span><select id="selectform_add0" name="Select' + question_index +'" onchange="change()"><option value="Text">Text</option></select></span></td></tr></table><table><tr><th class="input_size"><input type="text"  value="Answer" name="Answer' + question_index + '" class="Question_answer" onchange="change_value(this)"></th></tr></table><br><br>';
	div_id.appendChild(new_question_block);

}
function html_check() {
	div_id = document.getElementById('data');
	count_number_of_child = div_id.childElementCount;
	console.log(count_number_of_child = div_id.childElementCount);
	html = document.getElementById('html');
	console.log(html.innerHTML);
	console.log(count_number_of_child = div_id.childElementCount);
}
function change_value(input) {
	input.setAttribute("value",input.value);
}








</script>