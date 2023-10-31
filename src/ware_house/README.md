# KCRM  
### СКЛАД анализ и структура, в разработке: 

## Таблица "товары":  
Name | Data type | Size	| Note  
---- | ----- | ------ | -------
Товар | character varying | 250 | Наименование  
Код тов. | character varying | 150 | Код товара  
Артикул | character varying | 150 | Артикул товара  
Ед изм. | character varying | 10 | Ед изм  
Кол-во | int | 4 | Кол-во товара  
Цвет_1 | character varying | 20 | Цвет 1  
Цвет_2 | character varying | 20 | Цвет 2  
Цвет_3 | character varying | 20 | Цвет 3  
Цена | money | 8 | Цена товара  
Поставщик | character varying | 100 | Поставщик  
Клиент | character varying | 100 | Клиент имя  
Дата изг. | date | 4 | Дата изготовления  
Годен до | date | 4 | Срок годности до  
Сертификат | bool | 1 | Наличие сертификата  
Описание  | text | | Описание товара  

## Таблица "клиенты":  
Name | Data type | Size	| Note  
---- | ----- | ------ | -------
Клиент | character varying | 100 | Клиент имя  
Название | character varying | 150 | Полное наименование  
Контакт_1 | character varying | 100 | Лицо из фирмы должность  
Контакт_2 | character varying | 100 | Лицо из фирмыдолжность  
Адрес | character varying | 150 | Адрес
Доп инфо | text | | Доп инфо  

## Таблица "поставщики":  
Name | Data type | Size	| Note
Поставщик | character varying | 100 | Краткое имя
Название | character varying | 150 | Полное наименование
Телефон_1 | character varying | 50 | Номер телефона 
Телефон_2 | character varying | 50 | Номер телефона
Адрес | character varying | 150 | Адрес
Доп инфо | text | | Доп инфо
