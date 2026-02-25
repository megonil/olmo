project('olmo', 'c', default_options: 'c_std=gnu11')

unity_dep = dependency('unity')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m')

deps = [m_dep]

source = files(
	'array.c',
	'exec.c',
	'init.c',
	'lexer.c',
	'parser.c',
	'repl.c',
	'sourcemgr.c',
	'table.c',
	'utils.c',
	'value.c',
)

executable('olmo', source + files('main.c'), install: true, dependencies: deps)

test_source = files('test/main.c')
test_executable = executable('olmotest', source + test_source, dependencies: deps + unity_dep)

test('olmotest', test_executable)
