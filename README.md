# minishell
❓к Толяну
- Папка minishellmake не нужна? без нее все собирается
- Что за g_lobal_status?
- Зачем нужен char **copy_env? 
- Почему ctrl+C при пустом prompt предлагает ввести команду (у меня ctrl+C корректно отрабатывает без handler’a)
- Почему ctrl+\ при пустом prompt съедает пробел

❓к себе
? как получить для PIPE и REDIRECT t_ast_node->fd_in,  t_ast_node->fd_out
? норм, что при вызове get_env_value_by_name_from_envs из get_env_var_value_to_saver тоже увеличивается msh_ctx->cur_env_vars_len?
? можно ли сделать универсальную ф-ю t_env  *get_last_node(t_env *head) для любого типа? void *head не вариант, так как ошибка компиляции head->next (можно вторым аргументов передавать тип, для этого создать енам, и внутри ф0и делать приведение типов)
? почему без free_env_lst все равно нет утечек: малочу в ф-и get_envs
?echo, pwd: аргументы: char **argv, int fd  //echo a  > test вывод сразу в test или мне все таки не нужен fd, так как если он не 1, то подмена произойдет выше   *открытие и закрытие fd должно быть на вызывающей стороне
//при редиректе:  создать файл / открыть файл / открыть файл на дописывание

echo [-n] +
pwd +
exit + -
cd + ?
env
export + ?
unset +

◦ echo + with option -n
//echo без аргументов ◦ cd + ? with only a relative or absolute path  // если аргументов > 1, cd игнорирует второй аргумент
// ERROR: return (-1);
◦ pwd + with no options
◦ exit + - with no options  //убиваю через SIGKILL
// у exit может быть только 1 аргумент, если более - exit выкидывает ошибку
// если аргумент - число процесс завершается с n % 255 код должен быть [0, 255]
//если введено слишком большое число - ошибка
◦ env + - with no options or arguments
//env выводит экспортированные переменные, т.е. те переменные, которые передадутся в процесс-ребенок, в процесс родителя-нет
//экспортированные переменные = после команды export
//если экспортирована переменная без значения, она не отображается env и не передается ребенку (с пустым значением “” - отображается и передается) //+env не отображает переменные без значения, отображаемые в тот же момент времени export
//+если export отображает D=“”, то env - D= //+env не кидает ошибку, если переменная начинается с цифры/ специального символа 
 //+если писать имя несуществующей переменной без значения: bash-3.2$ env TEEST   ->  env: TEEST: No such file or directory  //ТОЧНЕЕ имя переменной, к директории которой нет доступа bash-3.2$ env HOME -> env: HOME: No such file or directory
TEST=test: Если директории нет, то ничего не выводится: env TEST 
?? почему не выводится test, если я создала файл test в текущей директории со всеми правами/создала директорию test со всеми правами
//+ bash-3.2$ env B C=l   ->    env: B: No such file or directory
//если добавили name=value1, потом изменили с помощью env на value2, env выведет сразу value2, следующий export - value1
//env TEST=test выводит с новой переменной, но при следующем вызове env ее уже нет (не в следующем промпте, а именно в вызове env L1=SEX^KIRILL & env, хотя так как мы не обрабатываем &, то можно считать, что в следующем промпте)
//TEST’=‘test    TEST”=“test
◦ export with no options
//+export без аргументов выводит переменные в алфавитном порядке
//создайте две переменные и экспортируйте одну из них: var1=1; export var2=2
? не реализована сортировка в алфавитном порядке по не первым буквам (мб не делать)?
? AS IS: export сортирует реальный список envs (если в следующем prompt после export вызвать env)?
//+export TEST=test ничего не выводит, при следующем вызове export есть TEST и при вызове env есть
//добавленные через export переменные должны быть в следующем prompt, через env - нет, только в текущем (но должно выполняться [env KIRILL=KATYA | wc -l], т.е. в текущем промпте должна запоминаться новая переменная) //можно в ноде envs хранить информацию о том, является ли переменная «экспортированной» или нет. И в конце каждого prompt удалять неэкспортированные переменные
//+export A B //создаст 2 переменные окружения без значения: A B
//+можно создавать без значения //export A B
//+export C=D
//+export E"="F 	K’=‘L
//+протестить, когда команды будут выполняться из ast_nodes после парсинга: //bash-3.2$ export C = D   -> bash: export: `=': not a valid identifier при этом C  D  создаются (считается как 3 разных токена)
//+export LOVE=   ->    declare -x LOVE
//+export LOVE=   ->    declare -x LOVE=""
//+export LO LVE="K" -> создает 2 переменные окружения
//+изменение существующей переменной окружения
//+за одну команду изменять одну и ту же переменную ◦ unset with no options
//+unset
//+unset A B
//+unset Y -> пусто, хотя такое переменной нет 
//+bash-3.2$ unset A=B -> bash: unset: `A=B': not a valid identifier //имена переменных окружения могут состоять только из букв или _ (* прочитать в сабжекте, нужно ли обрабатывать)  //+bash-3.2$ unset A# D -> bash: unset: `A#': not a valid identifier //при этом D удаляется
//unset должна принимать именно t_env **envs, иначе не обновляется снаружи “head”



Lexer + Parser
+договорились при незакрытой кавычке выдавать ошибку  + следующий промпт(в сабжекте Not interpret unclosed quotes) выдавать ошибку / мысленно подставить закрывающую кавычку
- [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] WTF при незакрытых кавычках каждого вида “smth’/‘smth”: пофиксила доп ифом после single_quote_lexer/double_quotes_lexer

*исполняемые файлы - обычные команды MSH_CMD = команда + аргументы 
*список списков с командами между пайпами (и редиректами) 
*env — нуль-терминальный массив указателей на строки переменных окружения. Каждая строка в формате ИМЯ=ЗНАЧЕНИЕ
*в односвязном списке хранить ключ->значение (нп переменные окружения: void *ключ(имя переменной)->void *значение(значение переменной),  в лексере при определении типа токенов в key=“, value=все что между “” )

wtf
+bash-3.2$ echo '' "''" '' //пустота в одинарных, блок двойных, пустота в одинарных
'' 
+bash-3.2$ echo "'''''" //-> в двойных кавычках одинарные не работают ~ блок двойных кавычек
''''' 
+bash-3.2$ echo "''' $USER   ''" //блок двойных => внутри работает разыменование
''' ekaterinasvincickaa   ‘’ +bash-3.2$ echo '"'' $USER   ''"' //двойная в одинарных, блок одинарных, двойная в одинарных
" $USER   " +bash-3.2$ echo "'"''' $USER   '''"'" //одинарная в двойных, пустота в 1-ых, блок 1-ых, пустота в 1-ых, одинарная в двойных
' $USER   '
+bash-3.2$ echo ''a' $USER   'a'' //пустота в 1-ых, a, блок одинарных, a, пустота в 1-ых
a $USER   a
+bash-3.2$ echo 'a'' $USER   ''a' //три блока в одинарных
a $USER   a
+ bash-3.2$ echo '"''' $USER   '''"'
" ekaterinasvincickaa " 
//двойная в 1-ых, пустота в 1-ых, пробел => начинается 2-ой токен, блок без кавычек, пробел => начинается 3-ий токен, 
bash-3.2$ echo "'"''' $USER   '''"'" | wc -w      -> 3

! раскрывать переменные окружения при лексинге, чтобы не запоминать, из кавычек какого типа получили токен

*все что между “” - токен (echo "$USER" -> heboni; echo "'$USER'" -> ‘heboni’) если “”, подставляем переменную окружения
*’’ - сильные кавычки, “” - слабые кавычки
* в ‘’ ничего не парсится и не выполняется (кроме случаев когда ‘’ внутри “”)
*+в “” подставляются переменные окружения
*+все что между ‘’ shell должен воспринимать как текст, а не как команды (echo '$USER' -> $USER;  echo '"$USER"' -> "$USER")

SIGNALS
*SIGINT: Ctrl+C
*SIGTSTP: Ctrl+\
*SIGQUIT: Ctrl+D

CMD->PATH
*subject: Search and launch the right executable (based on the PATH variable or using a relative or an absolute path). 
*bash-3.2$ ./minishell/minishell/minishell - relative path (находясь в 21school-main запускается мой минишелл)
*bash-3.2$ ../minishell/minishell/minishell - relative path (находясь в 21school-main/libft запускается мой минишелл)
*bash-3.2$ /Users/ekaterinasvincickaa/Documents/21_school/21school-main/minishell/minishell/minishell - absolute path (находясь в любой директории запускается мой минишелл)
* чтобы получить CMD->PATH нужно поискать исполняемый файл команды в директориях, которые прописаны в переменной окружения PATH между двоеточиями
*большая часть знакомых команд в ~/bin/
* ls (с заходом в PATH) , ./ls (поиск в директории, отдельно обработать, после весь ввод - аргументы) =>
Если один из таких случаев /ls; ./ls, ../ls (вместо ls мб более сложный путь, то в PATH искать не надо)
*при нахождении в / команды ls; bin/ls; bin/./ls дают одинаковый результат
*/bin/ls и ls дают одинаковый результат из любых директорий
*stat - для поиска бинарников в директориях из $PATH структуре хранить
*при экспорте апдейтить PATH ??

REDIRECT
-echo abc>text.txt = echo 'abc'>text.txt (если файла нет - открыть файл на создание, иначе - на перезапись)
->> (если файла нет - открыть файл на создание, иначе - на запись в конец файла)
?cat > text должно ли это работать (после cat ввод, останавливается с помощью ctrl D)
-< should redirect input (< text: на экран выведется содержимое text)

bash-3.2$ echo lol>>file //ОК
bash-3.2$ echo lol >>file //ОК
bash-3.2$ echo lol>> file //ОК
bash-3.2$ echo new ">" file  -> new > file
bash-3.2$ echo new '>' file   -> new > file
bash-3.2$ echo A=B > file $USER //cat file -> A=B ekaterinasvincickaa
bash-3.2$ echo abc > file1 file2    //cat file -> abc file2 //cat file2 -> cat: file2: No such file or directory
bash-3.2$ text1 > text2 -> bash: text1: command not found //при этом создастся файл text2 в текущей директории
bash-3.2$ echo smth > Music   //bash: Music: Is a directory

bash-3.2$ tr 'a-z' 'A-Z' < file   -> A=B EKATERINASVINCICKAA
bash-3.2$ tr 'a-z' 'A-Z' < file3 -> bash: file3: No such file or directory
bash-3.2$ cat < file   ->    A=B ekaterinasvincickaa 
*то есть    -если редирект правый >(перенаправляющий вывод)то сперва выполняется часть левее редиректа, после запись в файл справа
  -если редирект левый < перенаправляющий ввод (в левую часть ввод не из STDIN, а из дескриптора, который приходит из правой части), то сперва выполняется часть левее редиректа, потом часть правее. файл справа надо открыть на чтение, если его нет - ошибка
*при левом < редиректе нужны команды(cat), которые берут что-то из STDIN (echo, например, не берет из stdin данные, а из argv)

bash-3.2$ echo abc > file1 > file2 //cat file1  -> ПУСТО //cat file2 -> abc
bash-3.2$ sort < file1 < file2 -> X Y Z //в file1 было C B A, в file2 - Z Y X
*в одной команде по одному редиректу учитывается: последний перенаправляющий вывод>, последний перенаправляющий ввод<
bash-3.2$ sort < file1 < file2 -> bash: file1: No such file or directory   //хотя file2 есть
bash-3.2$ sort < file1 < file2  ->bash: file2: No such file or directory  //хотя file1 есть
*в служебную информацию о папе входит тип редиректа и файл, который нужно открыть 
bash-3.2$ cat lol < lol3          -> smth
bash-3.2$ cat < lol3 lol          -> smth
bash-3.2$ cat lol3                  -> smth3
bash-3.2$ cat lol                    -> smth

PIPE
*если в команде до пайпа ошибка, команда после пайпа отрабатывает независимо “-sort < file > newFile | echo abc”
*команда от пайпа до пайпа  sdarci:
sort < file > newFile | echo abc (не работает)
sort < file > newFile | echo abc | wc > file2 (левая часть не работает, правая часть после первого пайпа работает)
echo abc > file1 > file2 (создается только file2, должен и file1) sort < file1 < file2		(ругается на file2, должен - на file1)
cat lol | cat > lol          (cat: lol: No such file or directory такой ошибки не должно быть)

checklist
+ echo "'$USER'" -> value of user
+ echo '"$USER"' -> "$USER"
+ echo $ -> $
+ echo 123 $lol -> 123
+ echo "cat lol.c | cat > lol.c" (1 аргумент)


- [ ] ?(что за команда такая) cat lol | cat > lol //если выполнить без файла lol в директории - он создастся //!!! Если выполнить только cat lol без файла в директории -> cat: lol.c: No such file or directory //если выполнить только правую часть cat > lol, создастся файл lol + ожидание ввода из stdin
//если файл lol был непустой
bash-3.2$ cat lol
kool'
bash-3.2$ cat lol | cat > lol
bash-3.2$ cat lol
bash-3.2$ 

bash-3.2$ echo kool"'" > lol
bash-3.2$ cat lol
kool'
bash-3.2$ cat lol | cat >> lol
bash-3.2$ cat lol
kool'
kool’
bash-3.2$ cat lol | cat > lol
bash-3.2$ cat lol

bash-3.2$ echo kool"'" > lol
bash-3.2$ cat lol | cat
kool'

bash-3.2$ cat lol
smth
bash-3.2$ cat lol | cat > lol1
bash-3.2$ cat lol1
smth

bash-3.2$ cat < lol1
smth
bash-3.2$ echo abc > lol2
bash-3.2$ cat lol2
abc
bash-3.2$ cat lol | cat > lol1 < lol2
bash-3.2$ cat lol1
abc

bash-3.2$ cat lol | cat > lol1 < lol2 > lol3
bash-3.2$ cat lol1
bash-3.2$ cat lol3
abc

bash-3.2$ cat lol | cat | cat
smth
bash-3.2$ cat lol | cat | cat > lol3
bash-3.2$ cat lol3
smth

bash-3.2$ cat lol | cat | > lol3    //второй пайп взял из STDOUT smth и перевел в STDIN правой части, но никто не считал
bash-3.2$ cat lol3
bash-3.2$ cat lol
smth

bash-3.2$ cat lol | cat > lol1 <
bash: syntax error near unexpected token `newline'
bash-3.2$ cat lol | cat > lol1 < lol2 >
bash: syntax error near unexpected token `newline'

- [ ] Делать список ast_node от пайпа до пайпа (может ли быть несколько редиректов между пайпами) //если справа от пайпа ничего нет, у Толи ошибка
- [ ] Изменить получение ast_node типа REDIRECT (после > должен быть fd_out токен-файл, иначе-ошибка), разобрать кейсы, когда после > несколько токенов
    - [ ] добавить в парсер корректную обработку $? как отличить $? “$?” ‘$?’ сейчас парсится одинаково
	bash-3.2$ echo $? '$?'    ->    0 $? bash-3.2$ echo $? "$?"   ->   0 0 //можно записывать в exeption_indexes  //если войти в bash и сразу запросить echo $? -> 0
- [ ] переписать exit, buildins + no leaks
- [ ] запустить с флагами -Wall -Werror -Wextra
- [ ] add_history / rl_clear_history история prompt
- [ ] Запустить на линуксе
- [ ] Научиться получать исполняемые файлы команд t_ast_cmd->path
- [ ] Попробовать сделать маленький тестовый проект и там запустить отладку
- [ ] Как обрабатывать 2 пайпа подряд
      bash-3.2$ echo ||| //bash: syntax error near unexpected token `|'
      bash-3.2$ echo ||  //> 
- [ ] Регресс (протестить вложенные кавычки) echo $AB
- [x] $USER"$LANG" 1 4 | 2    после трех запусков подряд object 0x53555f6e6561616b: pointer being freed was not allocated echo "M$TER$USER" | wc -l < file   или   a | | <
- [x] Добавить учет special_indexes при tokens -> ast_nodes cmd->argv
- [x] Протестить: добавить обработку пайпов | '|' "|" ls| wc -l       +’ls'| wc -l      +”ls”| wc -l 
- [x] Как отличить редиректы/пайпы в кавычках от настоящих редиректов/пайпов | '|' | "|" -?????мб редиректы/пайпы в кавычках сохранять в кавычках в tokens[token_n] ???? Как отделять “|” от ‘”|”’ -можно сохранять в одинарных кавычках, тк в одинарных нельзя вывести пайп можно )))))))bash-3.2$ echo "'""|""'"      ->        ‘|’   (только случаи когда в кавычках только один из | > >> < <<, остальные случаи правильно обработаются) -не выделять редиректы/пайаы в отдельные токены и разбираться с ними уже при составлении t_ast_node (я не пойму, какие редиректы были в кавычках, какие - нет: случай > не отличим от “>” при текущей реализации) ❗️-когда пайп в кавычках, он воспринимается как аргумент => по общим правилам вычленения токенов не могу отличить “|” ‘|’ от |  => если токен - символ пайпа, то сохраняю индекс этого токена в специальный массив интов: special_indexes содержит номера тех токенов, которые являются пайпами-строками (</<</>/>>/| в ‘/“) bash-3.2$ echo f "|" wc -l      ->      f | wc -l bash-3.2$ echo f '|' wc -l       ->      f | wc -l bash-3.2$ echo f | wc -l          ->     1
- [x] Плавающая ошибка❗️ иногда в cmd->argv не сохраняется [0] элемент, чаще всего при 2/3-ех элементах, мб после добавления free уйдет -> не ушла(( был случай, когда не сохранился [1] элемент +после 10 промптов поймала ошибку minishell(8417,0x1132b0600) malloc: Heap corruption detected, free list is damaged at 0x600000034280 *** Incorrect guard value: 0 minishell(8417,0x1132b0600) malloc: *** set a breakpoint in malloc_error_break to debug
- [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] - [x] bash-3.2$ echo "M$TER $USER" ->M ekaterinasvincickaa (1 аргумент) bash-3.2$ echo "M$TER$USER" ->Mekaterinasvincickaa bash-3.2$ echo M$TER $USER -> M ekaterinasvincickaa (2 аргумента)
- [x] сега при пробеле
- [x] Утечки: при каждом следующем prompt (посмотреть, это утечки readline или мои)
- [x] Утечки в get_env в ф-и get_env_value_to_save нет утечек при вызове из heboni_tests мб утечки из-за того, что я выделаю под tokens[token_n] в malloc памяти больше, ставлю ‘\0’ и остается лишние ячейки после (хотя вряд ли, без envs все ок)
- [x] Добавить обработку редиректов
- [x] Зачем мне нужен был аргумент handle_quotes🧐?   Убрать его
- [x] - [x] доработать single_quote_token_saver, double_quotes_token_saver
- [x] realloc  char **tokens
- [x] Утечки при текущей архитектуре leaks --atExit -- ./a.out +без ввода переменных окружения утечек нет
- [x] Вношу envs в lexer
- [x] - [x] e'c'"h"o 90  e"c""h"o 90 88    починила, добавив return I после каждого if в single и double
- [x] ec'h'"o" 90 +    e'c'"h""o" 9 8       ->        echo 9 8Not closed quote "
- [x] "e"'c'"h"o 9 8 (было echo98) +  'e''c'"h""o" 9 8+   "e"'c'"h""o" 9 8+   e'c'ho 90 +  
- [x] почему в видео говорится что “smth”’smth’, это 1 аргумент:  touch “smth”’smth’ создает 1 файл smthsmth (touch "$USER"'smth' создает ekaterinasvincickaasmth) (touch "smth"new -> smthnew) (touch "smth"$TERM -> smthxterm-256color)

'lil' "pip" 'lil' 'pip'
"lil" "pip" "lol"
lil lol pip

'lil''lol'
'lil''lul''lol'
"lil""lul""lol"
'lil'"lul"
"lil"'lul' "lil"'lul'"lol" 'lil'"lul""lol' 	->	Not closed quote " 'lil'"lul"'lol'  
bash-3.2$ echo sis''pis''    ->  sispis +
bash-3.2$ echo sis'"pis"'   ->  sis"pis" +
bash-3.2$ echo simple' qoutes'"##"    ->  simple qoutes## +
bash-3.2$ "echo" abc      ->  abc +
bash-3.2$ "echo" "abc"   ->  abc +
bash-3.2$ 'echo' "abc"    ->   abc +
bash-3.2$ "echo abc" (1 arg) +
bash: echo abc: command not found
bash-3.2$ 'echo abc'  (1 arg) +
bash: echo abc: command not found bash-3.2$ echo smth"new"  ->  smthnew + bash-3.2$ echo smth'new'    ->  smthnew + lil"lul"'lol' lil'lul'"lol" 'lil'lul "lil"lul
bash-3.2$ ec"h"o 90     ->  90 +
bash-3.2$ ec'h'o 90      ->  90 +
bash-3.2$ e''c''h''o 90  ->  90(кавычки не являются символом-разделителем) +
bash-3.2$ ec"h "o         -> bash: ech o: command not found +
bash-3.2$ e' 'c''h''o 90 -> bash: e cho: command not found +
ec'h'"o" 90 + e'c'"h""o" 9 8 + ec'h'"o" 90 + e'c'"h""o" 9 8 +
"e"'c'"h"o 9 8 +
'e''c'"h""o" 9 8 +
"e"'c'"h""o" 9 8 +
e'c'ho 90 + ech"o" 90 + ech'o' 90 + ec'h'"o" 90 + smth simple ? +



bash-3.2$ echo '$USER'    -> $USER
bash-3.2$ echo "$USER"   -> ekaterinasvincickaa
bash-3.2$ echo $TERM"$USER"  bash-3.2$ echo TERM" $USER" -> TERM ekaterinasvincickaa bash-3.2$ echo $U"S"ER   -> SER bash-3.2$ echo $U'S'ER    -> SER bash-3.2$ echo $U"SE"R   -> SER bash-3.2$ echo "$HOME $TERM" -> /Users/ekaterinasvincickaa xterm-256color      !!!!!!!!!!!!!!!- bash-3.2$ echo "$HOME$TERM"  bash-3.2$ echo "$HOME"" $TERM" -> /Users/ekaterinasvincickaa xterm-256color  bash-3.2$ echo $TERM"$USER  bash-3.2$ echo $USER$TERM -> ekaterinasvincickaaxterm-256color 
bash-3.2$ echo $HOME'$TERM' bash-3.2$ echo $HOME'smth' -> /Users/ekaterinasvincickaasmth
bash-3.2$ echo 'best'"$USER"   -> bestekaterinasvincickaa
bash-3.2$ echo ' good'$TERM    ->  
 goodxterm-256color
bash-3.2$ echo$USER  -> bash: echoekaterinasvincickaa: command not found bash-3.2$ echo $TERM $ HOME 
bash-3.2$ echo $          ->  $
bash-3.2$ echo $a  -> //возвращает следующий промпт  

парсится в 3 токена: null, |, null bash-3.2$ echo '|'        ->      |
      bash-3.2$ echo ''|''      ->      bash: : command not found (эти ошибки на уровне исполнителя выявятся)       bash-3.2$ echo ""|""    ->     bash: : command not found



bash-3.2$ echo nk | wc -l
       1
bash-3.2$ echo nk '|' wc -l
nk | wc -l
bash-3.2$ echo nk "|" wc -l
nk | wc -l
bash-3.2$ ls | grep test
test
bash-3.2$ ls |grep test
test
bash-3.2$ ls|grep test
test
bash-3.2$ ls| grep test //ОК
test


*для запуска команд не билдинов запускаем форк, в ребенке исполняем через execve (тк команды из бинарников завершаются через exit, а нам нельзя чтобы основная программа shell завершилась)
*status из waitpid(.., int *status, ..) используется для того, чтобы знать с каким кодом завершился ребенок, и возвращать код завершения предыдущей команды при запросе $?, для считывания кода завершения ребенка есть макросы
*команды билдины запускаем из потока-родителя (думаю, можно тоже из ребенка)
*в execve передавать массив чаров , у которых null в конце 
*в зависимости от того, какой redirect последовательность выполнения нод разная
*хранить переменные в ctx, в каждой ноде хранить указатель на этот ctx ?? Сейчас отдельная переменная ctx

Лист “простой команды”
-char *путь к бинарнику
-аргументы команды char **argv (имя команды, аргументы команды)
-переменные окружения char **envp (нужны ли?)
-указатель на left-child
(лист пайпа:  +указатель на right-child)
(? указатель на prev лист)



-exit=ctrl+D
?echo ${VAR} = echo $VAR //нужно ли обрабатывать фигурные скобки
-если ввести echo $ и нажать таб 2 раза, выведутся все возможные значения, ктр можно подставить после$

0 - STDIN
1 - STDOUT
2 - STDERROR

int fd[2];
fd[0] - дескриптор для чтения  fd[1] - дескриптор для записи pipe(fd); 
dup2(fd[1], 1);  //теперь 1 указывает на fd[1], т.е. теперь команды, в том числе вызывающиеся через execve, будут выводить результат не в STDOUT, а в fd-записи для пайпа  //лучше это делать в дочернем процессе, тк иначе во всей программе STDOUT “испортится”
// ls | grep “”; cat //в начале сохранять копию STDIN: int temp_0_fd = dup(0);
//после считывания из fd[0] пайпа, сделать так, чтобы 0 указывал на STDIN: dup2(temp_0_fd, 0);



1. команда history
2. bash-3.2$ ls /junk ls: /junk: No such file or directory bash-3.2$ ls /junk 2> error.txt //дескриптор файла стандартной ошибки == 2 bash-3.2$ cat error.txt ls: /junk: No such file or directory //ошибка будет перенаправлена в указанный файл // если после 2 поставить пробел ошибка не будет перенаправлен

1)Статья на русском https://github.com/eLEGIJA/minishell
2)Со списком статей https://github.com/markveligod/minishell 
3)Перенаправление ввода/вывода в Linux: https://cloud.timeweb.com/blog/perenapravlenie-vvoda-vyvoda-v-linux-ubuntu 
3)readline: http://wiki.linuxformat.ru/wiki/LXF117:readline 