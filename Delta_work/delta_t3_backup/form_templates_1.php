<?php
// Initialize the session
session_start();
 
// Check if the user is logged in, if not then redirect him to login page
if(!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true){
    header("location: index.php");
    exit;
}
$_SESSION['form_create_flag'] = 1;

?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Forms</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css">
    <style type="text/css">
        body{ font: 14px sans-serif; text-align: center; }
    </style>
</head>
<body>
	<center>
	<table>
		<tr>
			<td>
				<a href = "create_formv1.php"><img height=40% src="Blank.png" style="border:5px solid black"></a>
				<br>
				<center>Blank form</center>
			</td>
			<td>
				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			</td>
			<td>
				<a href = "contactform.html"><img height=40% src="contact_information.png" style="border:5px solid black"></a>
				<center>Contact Information</center>
			</td>
			
		</tr>
	</table>
	</center>	
</body>
</html>