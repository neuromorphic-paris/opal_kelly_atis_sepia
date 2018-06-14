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
        defines {'COMPILER_WORKING_DIRECTORY="' .. project().location .. '"'}
        configuration 'release'
            targetdir 'build/release'
            defines {'NDEBUG'}
            flags {'OptimizeSpeed'}
        configuration 'debug'
            targetdir 'build/debug'
            defines {'DEBUG'}
            flags {'Symbols'}
        for index, name in ipairs(configurations()) do
            configuration {'macosx', name}
                postbuildcommands {
                    'install_name_tool -change libopalkellyfrontpanel.dylib '
                    .. path.getabsolute('resources/libopalkellyfrontpanel.dylib')
                    .. ' '
                    .. path.join(path.join(project().location, name), project().name)}
        end
