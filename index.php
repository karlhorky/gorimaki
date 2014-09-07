<?php
  session_start();
  header("Cache-control : private"); // IE6 Fix
  echo '<?xml version="1.0" encoding="iso-8859-1"?>';
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">

  <head>
    <title>Gorimaki</title>
    <link rel="stylesheet" type="text/css" href="style.css" />
  </head>

  <body class="gameBody">
    <div id="introBG">&nbsp;</div>
    <div id="introTitle">Gorimaki</div>


    <div id="uNameForm">
      <form action="mainGame.php" method="POST">
        <input class="tInput" type="text" name="userName" value="Enter your name:" onFocus="javascript:if(this.value=='Enter your name:')this.value=''" />
        <input class="sInput" type="submit" value="Go" /><br/>
        <input type="checkbox" checked="checked" name="instr" value="checked" /> Instructions?
      </form>
    </div>
  </body>

</html>
