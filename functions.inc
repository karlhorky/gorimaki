<?php


function initBoard($level)
// Initializes the game board
{
  $emptyRow = array ("emp", "emp", "emp", "emp", "emp", "emp", "emp", "emp", "emp",
                     "emp", "emp", "emp", "emp", "emp", "emp", "emp", "emp", "emp",
                     "emp", "emp");
  $gameBoard = array ( $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow,
                       $emptyRow);

  $playerPos = initPlayer($gameBoard, $level);
  $goalPos = initGoal($gameBoard, $level, $playerPos);

  if ($playerPos <= $goalPos)
    $groundLevel = initGround($gameBoard, $goalPos, $level);
  else
    $groundLevel = initGround($gameBoard, $playerPos, $level);

  return $gameBoard;
} // initBoard



function initPlayer(& $gameBoard, $level)
// Initializes the player
{
  $pos = rand(0, 18);
  $gameBoard[$pos][0] = "player";

  for ($rCount = $pos + 1; $rCount < 20; $rCount++)
    randFullBrick($gameBoard, $rCount, 0);

  return $pos;
} // initPlayer



function initGoal(& $gameBoard, $level, $playerPos)
// Initializes the goal
{
  $pos = rand(1, 18);
  
  if ($pos >= $playerPos)
    $difference = $pos - $playerPos;
  else
    $difference = $playerPos - $pos;
  
  while ($difference < 5 || $difference > 9)
  {
    $pos = rand(1, 18);
    
    if ($pos >= $playerPos)
      $difference = $pos - $playerPos;
    else
      $difference = $playerPos - $pos;
    
  } // while

  $gameBoard[$pos][19] = "goal";

  for ($rCount = $pos + 1; $rCount < 20; $rCount++)
    randFullBrick($gameBoard, $rCount, 19);

  return $pos;
} // initGoal



function initGround(& $gameBoard, $lowestPos, $level)
// Initializes a ground level to play off of
{
  $groundLevel = $lowestPos + (2 + ($level / 5));
  if ($groundLevel > 19)
    $groundLevel = 19;

  for ($rCount = $groundLevel; $rCount < 20; $rCount++)
  {
    for ($cCount = 0; $cCount < 20; $cCount++)
      randFullBrick($gameBoard, $rCount, $cCount);
  } // for
  return $groundLevel;
} // initGround


function setLevelVars($level, & $nJumps, & $timeCount)
// Sets the number of jumps available and the timer until the player moves
{
  $difficulty = (int)($level/4) + 1;
  if ($difficulty > 5) $difficulty = 5;
  if ($difficulty < 1) $difficulty = 1;

  $nJumps = -$difficulty + 6;
  $timeCount = -$difficulty + 7;
} // setLevelVars








function checkInput(& $gameBoard, & $timeCount, $currBrick)
// Checks for input and modifies the gameboard accordingly
{
  if (isset($_POST["skipTurn"]))
    $timeCount--;

  else
  {
    for ($rCount = 0; $rCount < 20; $rCount++)
    {
      for ($cCount = 0; $cCount < 20; $cCount++)
      {
        $brkName = "brk_$rCount-$cCount";
        $brkName .= "_x";

        if (isset($_POST["$brkName"]))
        {
          $row = checkPlacement($gameBoard, $cCount);
          if ($row >= 0)
          {
            $gameBoard[$row][$cCount] = $currBrick;
            $timeCount--;
          } // if
        } // if
      } // for
    } // for
  } // else
} // checkInput


function checkPlacement($gameBoard, $cCount)
// Checks the user's placement choice and modifies accordingly
{
  for ($chCount = 18; $chCount >= 0; $chCount--)
  {
    if ($gameBoard[$chCount][$cCount] == "emp")
      return $chCount;
  } // for
  return -1;
} // checkPlacement


function randFullBrick(& $gameBoard, $row, $col)
// Assigns random full bricks to spaces specified in gameboard
{
  $rColour = rand(0, 11);

  switch ($rColour)
  {
    case 0:
      $brkColour = "db";
      break;
    case 1:
      $brkColour = "dg";
      break;
    case 2:
      $brkColour = "do";
      break;
    case 3:
      $brkColour = "dp";
      break;
    case 4:
      $brkColour = "dr";
      break;
    case 5:
      $brkColour = "dy";
      break;
    case 6:
      $brkColour = "lb";
      break;
    case 7:
      $brkColour = "lg";
      break;
    case 8:
      $brkColour = "lo";
      break;
    case 9:
      $brkColour = "lp";
      break;
    case 10:
      $brkColour = "lr";
      break;
    case 11:
      $brkColour = "ly";
  } // switch

  $gameBoard[$row][$col] = "images/full_brk_$brkColour";
} // randFullBrick


function randBrick()
// Returns random bricks
{
  $rColour = rand(0, 11);
  $rBasicShape = rand(0, 2);

  switch ($rColour)
  {
    case 0:
      $brkColour = "db";
      break;
    case 1:
      $brkColour = "dg";
      break;
    case 2:
      $brkColour = "do";
      break;
    case 3:
      $brkColour = "dp";
      break;
    case 4:
      $brkColour = "dr";
      break;
    case 5:
      $brkColour = "dy";
      break;
    case 6:
      $brkColour = "lb";
      break;
    case 7:
      $brkColour = "lg";
      break;
    case 8:
      $brkColour = "lo";
      break;
    case 9:
      $brkColour = "lp";
      break;
    case 10:
      $brkColour = "lr";
      break;
    case 11:
      $brkColour = "ly";
  } // switch

  switch ($rBasicShape)
  {
    case 0:
      $brkShape = "full";
      break;
    case 1:
      $brkShape = "full";
      break;
    case 2:
      $rSlopeShape = rand(0, 5);
      switch ($rSlopeShape)
      {
        case 0:
          $brkShape = "lhml";
          break;
        case 1:
          $brkShape = "lhrl";
          break;
        case 2:
          $brkShape = "llmh";
          break;
        case 3:
          $brkShape = "llrh";
          break;
        case 4:
          $brkShape = "mhrl";
          break;
        case 5:
          $brkShape = "mlrh";
      } // switch
  } // switch

  $imgString = "images/$brkShape";
  $imgString .= "_brk_$brkColour";

  return $imgString;
} // randBrick



function movePlayer(& $gameBoard, & $level, & $nJumps)
// Moves the player one block forward or at least tries to
{
  $playerPos = array();        // Position of player
  $currBrkPos = array();       // Position of current brick stood apon
  $adjCol = "";                // The adjacent column
  $adjSpcPos = array();        // Position of adjacent empty space
  $adjBrkPos = array();        // Position of adjacent brick
  $heightDiff = "";            // Height diff. between curr. and adj. spaces


  for ($rCount = 0; $rCount < 20; $rCount++)
  {
    for ($cCount = 0; $cCount < 20; $cCount++)
    {
      if ($gameBoard[$rCount][$cCount] == "player")
      {
        $playerPos = array($rCount, $cCount);
        $currBrkPos = array($rCount+1, $cCount);
        $adjCol = $cCount + 1;
        break;
      } // if
    } // for
  } // for

  for ($rCount = 19; $rCount >= 0; $rCount--)
  {
    if ($gameBoard[$rCount][$adjCol] == "emp")
    {
      $adjSpcPos = array($rCount, $adjCol);
      $adjBrkPos = array($rCount+1, $adjCol);
 
      break;
    } // if
  } // for  

  $heightDiff = $adjSpcPos[0] - $playerPos[0];

  if ($heightDiff < 2 && $heightDiff > -2)
  // If the slope is manageable
  {
    $moveState = testMoveValidity($gameBoard, $currBrkPos, $adjBrkPos, $heightDiff);
    
    if ($moveState == 0)
    // If a jump is necessary
    {
      if ($nJumps > 0)
      {
        movePlayerImage($gameBoard, $playerPos, $adjSpcPos);
        $nJumps--;
      } // if
      else
        return 0;
    } // else    

    else if ($moveState == 1)
    // If a jump is not necessary
      movePlayerImage($gameBoard, $playerPos, $adjSpcPos);

    else if ($moveState == 2)
    // If the player's won the game
      return 2;     
    
  } // if

  else if ($heightDiff >= 2 || $heightDiff <= -2)
  // If your horse is too high or too low for the adjacent brick
  {
    $moveState = testMoveValidity($gameBoard, $currBrkPos, $adjBrkPos, $heightDiff);

    if ($moveState == 2 && $nJumps > 0)
      return 2;

    if ($heightDiff >= 2)
    {
      if ($nJumps > 0)
        $nJumps--;
      else
        return 0;
    } // if
    else
      return 0;
  } // else if

  return 1;

} // movePlayer



function testMoveValidity($gameBoard, $currBrkPos, $adjBrkPos, $heightDiff)
// Tests the validity of a move, given the height difference and types of bricks
{
  $currBrkString = $gameBoard[$currBrkPos[0]][$currBrkPos[1]];
  $adjBrkString = $gameBoard[$adjBrkPos[0]][$adjBrkPos[1]];
  $currBrkType = strtok($currBrkString, "_");
  $adjBrkType = strtok($adjBrkString, "_");

  if ($heightDiff == 0)
  // If the adjacent block is even with the current block
  {
    if ($adjBrkType == "goal")
      return 2;

    return 1;
  } // if

  else if ($heightDiff == -1)
  // If the adjacent block is higher than the current block
  {
    if ($adjBrkType == "images/llmh" || $adjBrkType == "images/llrh" ||
      $adjBrkType == "images/mlrh")
      return 1;
    else if ($adjBrkType == "goal")
      return 2;
  } // else if

  else if ($heightDiff == 1)
  // If the adjacent block is lower than the current block
  {
    if ($currBrkType == "images/lhml" || $currBrkType == "images/lhrl" ||
      $currBrkType == "images/mhrl")
      return 1;
    else if ($adjBrkType == "goal")
      return 2;
  } // else

  else if ($heightDiff == -2 || $heightDiff == 2)
  // If the adjacent block is too high or too low, test if the goal is the 'brick'
  {
    if ($adjBrkType == "goal")
      return 2;
  } // else if  

  return 0;
} // testMoveValidity



function movePlayerImage (& $gameBoard, $currCoords, $mvCoords)
// Moves the image of the player
{
  $gameBoard[$currCoords[0]][$currCoords[1]] = "emp";
  $gameBoard[$mvCoords[0]][$mvCoords[1]] = "player";
} // movePlayerImage



function regenTime($level)
// Regenerates time to the game difficulty level's time
{
  $difficulty = (int)($level/4) + 1;
  if ($difficulty > 5) $difficulty = 5;
  if ($difficulty < 1) $difficulty = 1;

   return -$difficulty + 7;
} // regenTime



function drawStats($level, $currBrick, $nJumps, $timeCount)
// Draws the stats
{
  echo "<div id=\"levelStat\">";
    echo "<div id=\"levelStatHead\">";
      echo "Level";
    echo "</div>";

    echo "<div id=\"levelStatContent\">";
      echo "$level";
    echo "</div>";
  echo "</div>";

  echo "<div id=\"skipTurn\">";
    echo "<form method=\"POST\" action=\"mainGame.php\">";
      echo "<input class=\"sInput\" type=\"submit\" name=\"skipTurn\" value=\"Skip a Turn\" />";
    echo "</form>";
  echo "</div>";


  echo "<div id=\"imgStat\">";
    echo "<div id=\"imgStatHead\">";
      echo "Current Brick";
    echo "</div>";

    echo "<div id=\"imgStatContent\">";
      echo "<img class=\"gbImg\" src=\"$currBrick.gif\" />";
    echo "</div>";
  echo "</div>";


  echo "<div id=\"jumpsStat\">";
    echo "<div id=\"jumpsStatHead\">";
      echo "Jumps Remaining";
    echo "</div>";

    echo "<div id=\"jumpsStatContent\">";
      echo "$nJumps";
    echo "</div>";
  echo "</div>";


  echo "<div id=\"timeStat\">";
    echo "<div id=\"timeStatHead\">";
      echo "Time Remaining";
    echo "</div>";

    echo "<div id=\"timeStatContent\">";
      echo "$timeCount";
    echo "</div>";
  echo "</div>";
} // drawStats


function drawBoard($gameBoard)
// Draws the game board
{
  echo "<div id=\"gameBoard\">";
  
  echo "<form action=\"mainGame.php\" method=\"POST\">";

  for ($rCount = 0; $rCount < 20; $rCount++)
  {
    for ($cCount = 0; $cCount < 20; $cCount++)
    {
      $currImg = $gameBoard[$rCount][$cCount];
      if ($currImg == "emp" && $cCount > 0 && $cCount < 19)
        echo "<input class=\"gbImg\" type=\"image\" value=\"brk_$rCount-$cCount\"
          name=\"brk_$rCount-$cCount\" src=\"$currImg.gif\" />";
      else
        echo "<img class=\"gbImg\" src=\"$currImg.gif\" />";
    } // for
    echo "<br/>";
  } // for
  echo "</form>";
  echo "</div>";
} // drawBoard

?>
