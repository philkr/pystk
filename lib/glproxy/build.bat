cd /d %~dp0
python src\gen_dispatch.py --dir . registry\egl.xml
python src\gen_dispatch.py --dir . registry\gl.xml
python src\gen_dispatch.py --dir . registry\glx.xml
python src\gen_dispatch.py --dir . registry\wgl.xml
pause