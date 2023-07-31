<?php

require_once __DIR__ . '/app/Monitor.php';
require_once __DIR__ . '/vendor/autoload.php';

$dotenv = Dotenv\Dotenv::createImmutable(__DIR__);

$dotenv->load();

$monitor = new Monitor($_ENV['PATH_FILES']);

$monitor->monitor();