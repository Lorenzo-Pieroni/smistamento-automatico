<?php
include_once("include/funzioni.php");
$db = database_connect() or die("ERRORE DI CONNESSIONE AL DATABASE");
$data = $db->query("SELECT * FROM api_key") or die('ERRORE: ' . $db->error);
$result = $data->fetch_assoc();
$api_key = $result['api_key'];
$post_api_key= $_POST['api_key'];
if($_POST['api_key'] == $api_key){
$data = $db->query("SELECT * FROM pacchi where id = (SELECT MAX(id) FROM pacchi)");
$result = $data->fetch_assoc();
echo $result['id']."-".$result['corriere']."-".$result['cap']."-".$result['peso'];
$db->close();
}
?>
