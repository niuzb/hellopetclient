APPNAME="Adventure"
# options
buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ code for $APPNAME using Android NDK

OPTIONS:
-s	Build externals from source
-h	this help
EOF
}
while getopts "sh" OPTION; do
case "$OPTION" in
s)
buildexternalsfromsource=1
;;
h)
usage
exit 0
;;
esac
done

# paths

if [ -z "${NDK_ROOT+aaa}" ];then
echo "please define NDK_ROOT"
exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory
COCOS2DX_ROOT="$DIR/.."
APP_ROOT="$DIR/.."
APP_ANDROID_ROOT="$DIR"

echo "NDK_ROOT = $NDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"

# make sure assets is exist
if [ -d "$APP_ANDROID_ROOT"/assets ]; then
    rm -rf "$APP_ANDROID_ROOT"/assets
fi

mkdir "$APP_ANDROID_ROOT"/assets

# copy resources
for file in "$APP_ROOT"/Resources/*
do
if [ -d "$file" ]; then
    cp -rf "$file" "$APP_ANDROID_ROOT"/assets
fi

if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/assets
fi
done

cp "$APP_ANDROID_ROOT"/libs/libcrashme/libcrashme.so "$APP_ANDROID_ROOT"/libs/armeabi

find "$APP_ANDROID_ROOT"/assets -name .svn -print0 | xargs -0 rm -r -f

# remove test_image_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_image_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_rgba8888.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_rgb888.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_rgba4444.pvr.gz
rm -f "$APP_ANDROID_ROOT"/assets/Images/test_1021x1024_a8.pvr.gz

