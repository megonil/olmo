project('olmo', 'c', default_options: 'c_std=gnu11')

unity_dep = dependency('unity')

source = files(
	'array.c',
	'exec.c',
	'lexer.c',
	'parser.c',
	'repl.c',
	'table.c',
	'value.c',
)

executable('olmo', source + files('main.c'), install: true)

test_source = files('test/table.c')
test_executable = executable('olmotest', source + test_source, dependencies: unity_dep)

test('olmotest', test_executable)
