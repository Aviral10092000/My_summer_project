<?php
require_once "config.php";

$flag = 0;
$index = 1;
$sql = "INSERT INTO ".trim($_POST['tname'])." ";
$sql_columns = " (email,name,";
$sql_values = " VALUES ('".trim($_POST['email'])."','".trim($_POST['name'])."','";
for ($i=3; $i <count($_POST) ; $i++)
 {
	
	
	$post_var = 'Answer'.$index;
	$sql_columns = $sql_columns."Q$index,";
	$sql_values = $sql_values.$_POST[$post_var]."','";
	$index = $index + 1;
	
}

$sql_values[strlen($sql_values)-2] = ')';
$sql_values[strlen($sql_values)-1] = chr(0);
$sql_columns[strlen($sql_columns)-1] = ')';
$sql = $sql.$sql_columns.$sql_values;
echo $sql;
$stmt = $mysqli->prepare($sql);
$stmt->execute();
$stmt->close();
echo "your responses added successfully thanks!";

?>