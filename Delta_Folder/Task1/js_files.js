
	var sum_calorie = 0;
	var display
	function calculate() {
	var Age = document.getElementById("Age");
	var Height = document.getElementById("Height");
	var Weight = document.getElementById("Weight");
	display = 10*Weight.value + 6.25*Height.value -5*Age.value + 5;
	let x_y = display;
	localStorage.setItem("CALCULATE",display);
	localStorage.setItem("AGE", Age.value);
	localStorage.setItem("Height_1", Height.value);
	localStorage.setItem("Weight_1", Weight.value);
	document.getElementById("Display").value = x_y;
	}
	function myFunction_1() {
	let value_1 = document.getElementById("Food_item");
	console.log(value_1);
	localStorage.setItem("ITEMS",(value_1.value));
	myFunction_2();
	myFunction_3();
	myFunction_4();
	myFunction_5();
	}
	function myFunction_2() {
	let value_2 = document.getElementById("Carbohydrates");
	localStorage.setItem("CARBOHYDRATES",(value_2.value));	
	}
	function myFunction_3() {
	let value_3 = document.getElementById("Fats");
	localStorage.setItem("FATS",(value_3.value));
	}
	function myFunction_4() {
	let value_4 = document.getElementById("Calorie");
	localStorage.setItem("CALORIE",(value_4.value));
	var str = value_4.value.split("\n");
	for(var i =0;i<str.length;i++)
	{
		sum_calorie = sum_calorie + parseInt(str[i]);
	}
	if(sum_calorie>display)
		alert("Calorie intake exceded");
	if(sum_calorie==display)
		alert("Calorie Requirement is done for this day");
	}
	function myFunction_5() {
		let value_5 = document.getElementById("Water");
		localStorage.setItem("Water",(value_5.value));
		var str = value_5.value.split("\n");
		if(parseInt(str[0])>=1000)
		{
			alert("Water Requirement is done");
		}
		else if(parseInt(str[0])<1000)
		{
			alert("Water Requirement is not fullfilled");
		}
	}
	function Textarea_fill() {
	let value_1 = document.getElementById("Food_item");
	var a = localStorage.getItem("ITEMS");
	if(a!==null)
	value_1.value = a.split(",");
	let value_2 = document.getElementById("Carbohydrates");
	a = localStorage.getItem("CARBOHYDRATES"); 
	if(a!==null)
	value_2.value = a.split(",");
	let value_3 = document.getElementById("Fats");
	a = localStorage.getItem("FATS");
	if(a!==null)
	value_3.value = a.split(",");
	let value_4 = document.getElementById("Calorie");
	a = localStorage.getItem("CALORIE");
	if(a!==null)
	value_4.value = a.split(",");
	let x = localStorage.getItem("AGE");
	value_1 = document.getElementById("Age");
	value_1.value = x;
	let value_5 = document.getElementById("Water");
	a = localStorage.getItem("Water");
	value_5.value = a.split(",");
	let y = localStorage.getItem("Height_1");
	document.getElementById("Height").value = y;
	let z = localStorage.getItem("Weight_1");
	document.getElementById("Weight").value = z;
	let a_b = localStorage.getItem("CALCULATE");
	document.getElementById("Display").value = a_b;
	}


