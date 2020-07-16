#pragma once

#include <Arduino.h>

#include "Consts.h"

#include "FS.h"

#ifdef ESP32
#include "LITTLEFS.h"
#define LittleFS LITTLEFS
#endif
#ifdef ESP8266
#include <LittleFS.h>
#endif

/*
* Инициализация ФС
*/
bool fs_init();
/*
* Существование файла
*/
bool fileExists(const char* filename);
/*
* Удалить файл
*/
bool removeFile(const String filename, bool fail_if_not_exists = false);
/*
* Открыть файл на позиции
*/
File seekFile(const String filename, size_t position = 0);

/*
* Чтение строки из файла
* возвращает стоку из файла в которой есть искомое слово found
*/
const String readFileString(const String filename, const String to_find);

/* 
* Добовление строки в файл
*/
const String addFile(const String filename, const String str);

/*
* Запись строки в файл
*/
const String writeFile(const String filename, const String str);

/*
*  Чтение файла в строку
*/
bool readFile(const char* filename, String& str, size_t max_size = 4096);

/*
*  Размер файла
*/
const String getFileSize(const String filename);

bool copyFile(const String src, const String dst, bool overwrite = true);

const String getFSSizeInfo();

const String getConfigFile(uint8_t preset, ConfigType_t type);

void replaceFileContent(const char* filename, const char* newcontent, bool backup = true);
