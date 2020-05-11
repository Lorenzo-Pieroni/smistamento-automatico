<?php
function database_connect(){
  $host = "localhost";
  $user = "User";
  $password = "Password";
  $database = "smistamento";
  $db = new mysqli($host, $user, $password, $database);
  if($db->connect_error){
    return 0;
    }
    else{
        return $db;
  }
}
?>
