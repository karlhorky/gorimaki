<?php
  session_start();
  header("Cache-control : private"); // IE6 Fix
  echo '<?xml version="1.0" encoding="iso-8859-1"?>';
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">

  <head>
    <title>Gorimaki

    <?php
      if (isset($_POST['instr']) && $_POST['instr'] == "checked")
      {
        echo ": Instructions";
        $_SESSION["instr"] = 1;
      } // if
      else
        $_SESSION["instr"] = 0;
    ?>

    </title>
    <link rel="stylesheet" type="text/css" href="style.css" />

    <script language="javascript" type="text/javascript" src="functions.js">
    </script>
  </head>

  <body class="gameBody">
    

    

      <?php
        if ($_SESSION["instr"])
        // If instructions are requested
        {
          echo "<div id=\"introBG\">&nbsp;</div>";
          echo "<div id=\"introTitle\">Gorimaki</div>";

          echo "<div id=\"content\">";
            require "instr.inc";
          echo "</div>";
        }
        else
        // If the player wants to get into the game
        {
          require "functions.inc";
          

          if (!isset($_SESSION["level"]))
            $_SESSION["level"] = 1;
          
          if (!isset($_SESSION["gameState"]))
            $_SESSION["gameState"] = 1;
          else
          {
            if ($_SESSION["gameState"] != 1)
              $_SESSION["gameState"] = 1;
          } // else

          if (!isset($_SESSION["gameBoard"]))
            $_SESSION["gameBoard"] = initBoard($_SESSION["level"]);

          if (!isset($_SESSION["nJumps"]) && !isset($_SESSION["timeCount"]))
          {
            $_SESSION["nJumps"] = "0";
            $_SESSION["timeCount"] = "0";
            setLevelVars($_SESSION["level"], $_SESSION["nJumps"],
              $_SESSION["timeCount"]);
          } // if


          if (isset($_SESSION["currBrick"]))
            checkInput($_SESSION["gameBoard"], $_SESSION["timeCount"],
              $_SESSION["currBrick"]);

          
            


          if ($_SESSION["timeCount"] == 0)
          // If the time counter is at 0
          {

            $_SESSION["gameState"] = movePlayer($_SESSION["gameBoard"],
              $_SESSION["level"], $_SESSION["nJumps"]);

            if ($_SESSION["gameState"] == 1)
            // If the player's in the middle of a game
              $_SESSION["timeCount"] = regenTime($_SESSION["level"]);

          } // if


          echo "<div id=\"statsBG\">";
            echo "<div id=\"titleText\">Gorimaki</div>";
            echo "<div id=\"stats\">";
              $_SESSION["currBrick"] = randBrick();
              drawStats($_SESSION["level"], $_SESSION["currBrick"],
                $_SESSION["nJumps"], $_SESSION["timeCount"]);
            echo "</div>";
          echo "</div>";


          if ($_SESSION["gameState"] == 1)
          // If the player's in the middle of a game
            drawBoard($_SESSION["gameBoard"]);

          else if ($_SESSION["gameState"] == 0)
          // If the player has lost the game
          {
            foreach ($_SESSION as $key => $value)
            {
              if ($key != "gameState")
                unset($_SESSION[$key]);
            } // foreach            
            echo "<script language=\"javascript\" type=\"text/javascript\">loseGame();</script>";
          } // else if

          else
          // If the player has completed a level
          {
            $_SESSION["level"]++;
            foreach ($_SESSION as $key => $value)
            {
              if ($key != "level" && $key != "gameState")
                unset($_SESSION[$key]);
            } // foreach
            echo "<script language=\"javascript\" type=\"text/javascript\">levelComplete();</script>";
          } // else
          
        } // else
      ?>


  </body>

</html>
