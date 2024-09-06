## Contents

1. [Chapter I](#chapter-i) \
    1.1. [Readme!](#readme)
    1.2. [Level 1. Room 1.](#level-1-room-1)
2. [Chapter II](#chapter-i) \
    2.1. [Level 2. Room 1.](#level-2-room-1)

## Chapter I

## Readme!

\>
От разработчиков: \
Здравствуй, дорогой друг! \


Всё по папкам.

build - папка с готовым кодом и файлами текстовыми.

data - все функции, мейн, хэдерфайл.

libs - хранилище объектных файлов и библиотек.

make - содержит мейкфайл, который всё из data собирает в один файл в build.

Trash - всяко-разно собранное в процессе.

Vers - версии сборок, местами кривоватые.

Итоговый файл Game.exe, в папке build.

Чтоб он появился смонтировать мейком в папке make.

Команды стандартные, прописаны в мейке с комментариями.


## Level 1. Room 1.

***LOADING Level 1…***
***LOADING Room 1…***

Для корректной работы в группе Гит, обязательно создавайте отдельную от develop ветку.

develop - ветка для слияний уже готовых фич, что становится очевидно на схеме расположенной на следующей странице.
Это НЕ рабочая ветка, её можно тянуть и ненадо пушить.

Для начала работы создайте SSH ключ и сбросте в чат для его валидации на GitHub.

По пришедшей в ответ ссылке, склонируйте к себе develop.

## Генерация ключей и минимум команд достаточный для работы.

ssh-keygen

Ентер и всо что там нада

cat ~/.ssh/id_rsa.pub

git init

git branch "name"

git switch "name"

git branch -d "name"

git status

git add --all

git commit -m "name"

git push origin "name"

git merge "name" (from develop for overwrite it)

/







## Chapter II

## Level 2. Room 1.

>Не работайте в develop, пользуйтесь приведённой ниже схемой: 
>

![WorkWithGit](libs/GitRolePole.jpg)


