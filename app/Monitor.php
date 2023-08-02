<?php

require __DIR__ . '/../vendor/autoload.php';
require_once __DIR__ . '/Log.php';

use GuzzleHttp\Client;
use GuzzleHttp\Exception\RequestException;

class Monitor
{

    private $folderPath;
    private $previousFiles = [];

    public function __construct($folderPath)
    {
        echo "Aplicacion de automatizacion de Facturas \n";
        $this->folderPath = $folderPath;
        $this->previousFiles = $this->getPreviousFiles();
    }

    private function getPreviousFiles()
    {
        if (file_exists(__DIR__ . '/../previous_files.json')) {
            return json_decode(file_get_contents(__DIR__ . '/../previous_files.json'), true);
        } else {
            return [];
        }
    }

    public function monitor()
    {
        $dotenv = Dotenv\Dotenv::createImmutable(__DIR__ . '/../');

        $dotenv->load();

        while (true) {
            try {
                $currentFiles = array_diff(scandir($this->folderPath), ['.', '..']);

                $newFiles = array_diff($currentFiles, $this->previousFiles);

                if (!empty($newFiles)) {

                    $client = new Client();

                    foreach ($newFiles as $newFile) {

                        try {

                            $response = $client->post($_ENV['API_URL'], [
                                'verify' => __DIR__ . '/../key/cacert.pem',
                                'multipart' => [
                                    [
                                        'name' => 'factura',
                                        'contents' => fopen($this->folderPath . '/' . $newFile, 'r'),
                                        'filename' => 'factura.html'
                                    ],
                                    [
                                        'name' => 'api',
                                        'contents' => true
                                    ]
                                ]
                            ]);

                            $message = "Proceso realizado correctamente para el archivo $newFile | " . $response->getBody()->getContents();

                            echo $message  . "\n";

                            $logs = new Log($response->getStatusCode(), $message);

                        } catch (RequestException $e) {
                            
                            if ($e->hasResponse()) {
                                $response = $e->getResponse();
                                $statusCode = $response->getStatusCode();
                                $content = $response->getBody()->getContents();

                                $message = "Error: " . $content;

                                echo $message  . "\n";

                                $logs = new Log($statusCode,$message);
                                
                            } else {

                                $message = "Error: " . $e->getMessage();

                                echo $message . "\n";

                                $logs = new Log(500, $message);
                            }
                        }
                    }
                }

                file_put_contents(__DIR__ . '/../previous_files.json', json_encode($currentFiles));

                $this->previousFiles = $this->getPreviousFiles();
            } catch (Exception $e) {
                $logs = new Log(500, "Error: " . $e->getMessage());
            }
            sleep(5);
        }
    }
}
