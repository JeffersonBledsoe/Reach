PUSHD JUCE\extras\Projucer\Builds\VisualStudio2017
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe" Projucer.sln /p:Configuration=Release -DJUCER_ENABLE_GPL_MODE=1
start x64\Release\App\Projucer.exe
POPD
exit