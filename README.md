# TreeParser

TreeParser - библиотека, предоставляющая функционал для работы с деревом.

<p align="left">
    <a href="https://circleci.com/gh/gistrec/TreeParser/tree/develop">
        <img src="https://img.shields.io/circleci/build/github/gistrec/TreeParser/develop" alt="Build status">
    </a>
</p>

## Структура проекта
* `example` - демонстрационная программа
* `include` - заголовочные файлы библиотеки
* `src` - файлы реализации библиотеки
* `test` - Gtest'ы
* `Makefile` - набор инструкций для автоматизации сборки (библиотеки, демонстрационной программы и тестов)

## Особенности
* Разделитель у вещественного числа - точка

## Пример конфига

Для хранения дерева в файле был разработан специальный формат ([пример файла](https://github.com/gistrec/TreeParser/blob/develop/example/input.txt)).
Дочерние узлы  имеют отступ в 1 знак табуляции

Таким образом дерево
![](https://gistrec.ru/wp-content/uploads/2020/02/TreeParse.png "Пример дерева")
Записывается в конфиг как
```
8
	"bar"
		2.015
			9
		2015
		"2015"
	"baz"
		"foo"
		6.28318
		"hello"
```

## Пример использования

Для демонстрации работы библиотеки была создана [программа](https://github.com/gistrec/TreeParser/blob/develop/example/example.cpp), в виде консольного приложения, которая имеет следующие параметры:
* -i/--input - имя входного файла с сериализованным деревом;
* -o/--output - имя выходного файла, в которое будет сериализовано дерева

Программа десериализовывает дерево из файла input, печатает дерево на экран, и сериализовывает его в файл output.

## Доступные функции

* [`void print(const std::shared_ptr<Node>& tree, std::ostream& stream = std::cout)`](#print)
* [`void read(const std::string& filename, std::shared_ptr<Node>& tree)`](#read)
* [`void write(const std::string& filename, const std::shared_ptr<Node>& tree)`](#write)

## Описание функций

<a name="print"></a>
**`void print(const std::shared_ptr<Node>& tree, std::ostream& stream = std::cout)`** - Печатает дерево в поток

* `tree` - дерево, которое будет распечатано
* `stream` - поток вывода

---

<a name="read"></a>
**`void read(const std::string& filename, std::shared_ptr<Node>& tree)`** - Десериализовать дерево из файла.

* `filename` - файл, откуда нужно считать дерево
* `tree` - указатель, куда считается дерево

Исключения:
* TreeBadFile - если не удалось прочитать данные из файла
* TreeBadData - если в файле содержится ошибка

---

<a name="write"></a>
**`void write(const std::string& filename, const std::shared_ptr<Node>& tree)`** - Сериализовать дерево в файл.

* `filename` - файл, куда нужно сериализовывать дерево
* `tree` - указатель на дерево, которое нужно сериализовать

Исключения:
* TreeBadFile - если не удалось записать данные в файл
