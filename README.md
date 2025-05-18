# NerdFetch-C
C-реализация NerdFetch - программы для отображения информации о системе \*nix с использованием Nerdfonts (и других шрифтов)

## О программе
NerdFetch-C - это порт популярного shell-скрипта [NerdFetch](https://github.com/ThatOneCalculator/NerdFetch) на язык C. Он обеспечивает такую же функциональность и эстетику, но с преимуществами компилируемой программы.

## Скриншоты
*Nerdfont (По умолчанию)*
![Скриншот](https://github.com/ThatOneCalculator/NerdFetch/assets/44733677/37ea2a01-80e1-457b-b922-89cc708c527e)

*Phosphor Bold*
![Phosphor](https://github.com/ThatOneCalculator/NerdFetch/assets/44733677/07d2cc29-5a58-4a00-8a52-95ec2032988b)

*Cozette*
![Cozette](https://github.com/ThatOneCalculator/NerdFetch/assets/44733677/574e8417-adee-45cd-9a4e-68661240f458)

## Зависимости
- [Любой шрифт Nerdfonts](https://www.nerdfonts.com/font-downloads), [Cozette](https://github.com/slavfox/Cozette), или [Phosphor](https://github.com/phosphor-icons/homepage/releases/tag/v2.0.0)
- Компилятор C (GCC или Clang)
- Система сборки Meson
- Сборочный бэкенд Ninja

## Сборка и установка

### Предварительные требования
Убедитесь, что у вас установлены зависимости для сборки:

#### Arch Linux
```sh
sudo pacman -S gcc meson ninja
```

#### Debian/Ubuntu
```sh
sudo apt install build-essential meson ninja-build
```

#### Fedora
```sh
sudo dnf install gcc meson ninja-build
```

### Сборка и установка
```sh
# Клонирование репозитория
git clone https://github.com/AnmiTaliDev/nerdfetch-c.git
cd nerdfetch-c

# Настройка директории сборки
meson setup builddir
cd builddir

# Компиляция
meson compile

# Установка (опционально)
sudo meson install
```

### Запуск без установки
```sh
./nerdfetch
```

## Использование

```sh
# По умолчанию (Nerdfonts)
nerdfetch

# С использованием шрифта Cozette
nerdfetch -c

# С использованием шрифта Phosphor
nerdfetch -p

# С использованием Emoji
nerdfetch -e

# Показать версию
nerdfetch -v

# Показать справку
nerdfetch -h
```

## Особенности
- Кроссплатформенная поддержка различных \*nix систем
- Более быстрое выполнение в виде компилируемого бинарного файла
- Низкое потребление ресурсов
- Такой же внешний вид, как и у оригинального shell-скрипта
- Поддержка POSIX-совместимых систем

## Поддерживаемые операционные системы
- Linux (различные дистрибутивы)
- BSD-варианты (FreeBSD, OpenBSD, NetBSD)
- macOS

## Оригинальный проект
Это C-порт [NerdFetch](https://github.com/ThatOneCalculator/NerdFetch) от ThatOneCalculator.

## Лицензия
Этот проект лицензирован на тех же условиях, что и оригинальный NerdFetch.