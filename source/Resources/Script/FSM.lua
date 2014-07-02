--Í¨ÓÃ×´Ì¬»ú
state_machine={}

state_machine.new=function(initstate)  
   local fsm = state_machine
   fsm.transitions={}
   fsm.initstate = initstate   
   return fsm
end

function state_machine:add_transition(from,evt,to,guard,entry,action,leave)
	local transition =  transitions[from]
    local t = {to=to,guard=guard,entry=entry,action=action,leave=leave} 
    if transition then
        transition[evt]=t
    else
        transition={}
        transition[evt] = t
        transitions[from]=transition
    end
end 

function state_machine:do_transition(evt)
    local  row = assert(transitions[initstate] )    
    local  transition = row[evt]
    if not transition then return end
    assert(transition.to) 
    if transition.guard(initstate,evt,transition.to) then
		transition.entry(initstate,evt,transition.to)
        if transition.action(evt) then
			transition.leave(initstate,evt,transition.to) 
            initstate = transition.to
        end
	end
end 

function state_machine:post_event(evt)
	assert(evt)    
    do_transition(evt)
end 

function state_machine:process_event(evt)
	do_transition(evt)  
    if  front then 
        while front <= back do
            local event = events[front]
            events[front] = nil        
            front = front + 1
            do_transition(event)
        end
    end
end