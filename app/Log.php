<?php

require __DIR__ . '/../vendor/autoload.php';

use Carbon\Carbon;

class Log
{

    public function __construct($code, $message)
    {
        $this->insertLog($this->getLogMessage($code, $message));
    }

    private function getLogMessage($code, $message)
    {

        return "[$code] $message | " . Carbon::now() . "\n";
    }

    private function insertLog($log)
    {
        file_put_contents(__DIR__ . '/../logs/api.log', $log,FILE_APPEND);

        return true;
    }
}
