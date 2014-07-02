require("Script/FSM")

local fsm = state_machine.new(stopped_state)

fsm:add_transition(stopped_state,play_event,play_state,guard,void_,do_play,void_)
fsm:add_transition(play_state,pause_event,paused_state_guard,void_,do_pause,void_)
fsm:add_transition(paused_state,play_event,play_state,guard,void_,do_resume,void_)
fsm:add_transition(paused_state,stop_event,stopped_state,guard,void_,do_stop,void_)
fsm:add_transition(play_state,stop_event,stopped_state,guard,void_,do_stop,void_)

 

fsm:process_event(play_event)
fsm:process_event(stop_event)
fsm:process_event(pause_event)
fsm:process_event(play_event)
fsm:process_event(pause_event)
fsm:process_event(stop_event)
fsm:process_event(play_event)
fsm:process_event(stop_event)