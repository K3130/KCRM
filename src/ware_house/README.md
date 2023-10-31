# KCRM  
### СКЛАД анализ и структура, в разработке: 
Таблица "товары":  
Name	|Data type	|Size	|Note	|  
-----------------------------------------			  
Товар	 character varying	 250	 Наименование  
Код тов. character varying	 150	 Код товара  
Артикул	 character varying	 150	 Артикул товара  
Ед изм.  character varying	 10	 Ед изм  
Кол-во	 int		 	 4	 Кол-во товара  
Цвет_1	 character varying	 20	 Цвет 1  
Цвет_2	 character varying	 20	 Цвет 2  
Цвет_3	 character varying	 20	 Цвет 3  
Цена	 money		 	 8	 Цена товара  
Поставщик character varying	 100	 Поставщик  
Клиент	  character varying	 100	 Клиент  
Дата изг.	date		 4	 Дата изготовления  
Годен до	date		 4	 Срок годности до  
Сертификат bool			 1	 Наличие сертификата  
Описание text				 Описание товара  