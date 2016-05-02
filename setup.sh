SUBMODULES=("PluginXProtocols" "PluginXGooglePlay" "PluginXIosIap" "C2DXChartboost" "openssl-android")
for MOD in ${SUBMODULES[@]};do
    git submodule update --init --reference ../$MOD Vendor/$MOD
done
git submodule update --init --reference ../cocos2d-x cocos2d
git submodule update --init --reference ../cocos2d-x-lib Vendor/lib
cp Vendor/lib/EnvPrivate.h.sample Classes/EnvPrivate.h
cd cocos2d
yes | ./download-deps.py
cd ../
