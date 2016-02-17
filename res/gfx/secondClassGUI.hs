import Graphics.UI.Gtk

hello::(ButtonClass o)=>o->UI()
hello b = set b [buttonLabel:="Hello World"]

main::IO()
main = do
	initGUI
	windows<-windowNew

