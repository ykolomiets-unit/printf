def FlagsForFile( filename, **kwargs):
    return {
        'flags': [
            '-x',
            'c',
            '-Wall',
            '-Wextra',
            '-Werror',
            '-I./lib/Unity/src/',
			'-I./lib/Unity/extras/fixture/src',
			'-I./include',
			'-I./include/util',
			'-I./mocks'],
    }
