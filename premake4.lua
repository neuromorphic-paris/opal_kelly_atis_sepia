solution 'opal_kelly_atis_sepia'
    configurations {'release', 'debug'}
    location 'build'
    project 'opal_kelly_atis_sepia'
        kind 'ConsoleApp'
        language 'C++'
        location 'build'
        files {'source/*.hpp', 'test/*.cpp'}
        libdirs {'resources'}
        buildoptions {'-std=c++11'}
        linkoptions {'-std=c++11'}
        links {'pthread', 'opalkellyfrontpanel'}
        configuration 'release'
            targetdir 'build/release'
            defines {'NDEBUG'}
            flags {'OptimizeSpeed'}
        configuration 'debug'
            targetdir 'build/debug'
            defines {'DEBUG'}
            flags {'Symbols'}
        configuration {'macosx', 'debug'}
            postbuildcommands {
                'install_name_tool -change libopalkellyfrontpanel.dylib '
                .. path.getabsolute('resources/libopalkellyfrontpanel.dylib')
                .. ' '
                .. path.getabsolute('build/debug/opal_kelly_atis_sepia')}
        configuration {'macosx', 'release'}
            postbuildcommands {
                'install_name_tool -change libopalkellyfrontpanel.dylib '
                .. path.getabsolute('resources/libopalkellyfrontpanel.dylib')
                .. ' '
                .. path.getabsolute('build/release/opal_kelly_atis_sepia')}
