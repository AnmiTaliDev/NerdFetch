project('nerdfetch-c', 'c',
  version : '1.0.0',
  default_options : ['warning_level=3', 'c_std=c11'])

# Компилятор C
cc = meson.get_compiler('c')

# Зависимости
deps = []

# Исходные файлы
src_dir = 'src'
src_files = [
  src_dir / 'main.c'  # Путь к файлу в директории src
]

# Проверяем наличие необходимых библиотек
if host_machine.system() == 'linux'
  deps += cc.find_library('m', required : false)  # Математическая библиотека
endif

# Заголовочные файлы
inc_dirs = [include_directories(src_dir)]

# Исполняемый файл
executable('nerdfetch',
           sources : src_files,
           include_directories : inc_dirs,
           dependencies : deps,
           install : true)

# Установка документации
readme = 'README.md'
if run_command('[', '-f', readme, ']', check: false).returncode() == 0
  install_data(readme, 
               install_dir : get_option('datadir') / 'doc' / 'nerdfetch')
endif