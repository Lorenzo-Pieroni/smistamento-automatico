<?php
include_once("include/funzioni.php");
$db = database_connect() or die ("ERRORE DI CONNESSIONE AL DATABASE");
$data = $db->query("SELECT * FROM api_key") or die('ERRORE: ' . $db->error);
$result = $data->fetch_assoc();
$api_key = $result['api_key'];
$post_api_key= $_POST['api_key'];
if($_POST['api_key'] == $api_key){
$id_post = $_POST['id'];
echo $peso;
$db->query("UPDATE pacchi SET moved=1 WHERE id = '$id_post'") or die('ERRORE: ' . $db->error);
$db->close();
}
else {
  echo "API KEY WRONG";
}
?>
