ltl especificacion1 {
	[]( (Estado == PRIMERO && B2==1) || ( (Estado == SEGUNDO && B1==1))
}
//Cuando se encienda en algun momento se apagara
ltl especificacion2 {
	[]((C1== 1) -> <>(A1== 1));
}


mtype={PRIMERO,SEGUNDO,MOVE,UP, DOWN,STOP}
 int P1;
 int P2;
 int C1;
 int C2;
 int A1;
 int A2;
int control
int now;
int time_out;

active proctype ascensor(){
	estado=PRIMERO;
	do
	::(estado==PRIMERO)->atomic{
		if
		::(!C2 && (time_out <= now) && P2) -> P2=0; control =UP; B1=1; B2=1;estado=MOVE;
		:: C2 -> C2= 0; control =UP; B1=1; B2=1;estado=MOVE;

    	fi;
	}
	::(estado==MOVE)->atomic{
		if
		::A1 ->  A1=0;control =STOP; B1=0; time_out = now + 10;estado=PRIMERO;
        ::A2 -> A2=0;control =STOP; B2=0; time_out = now + 10;estado=SEGUNDO;
		fi;
	}
    ::(estado==SEGUNDO)->atomic{
		if
        ::(!C1 && (time_out <= now) && P1) ->  P1=0; control =DOWN; B1=1; B2=1;estado=MOVE;
		:: C1 -> C1=0; control =DOWN; B1=1; B2=1;estado=MOVE;
		
    	fi;
	}
	od;
}


active proctype entorno(){
	now=0;
	do
	::if
	    ::P1=1;
        ::P2=1;
        ::C1=1;
        ::C2=1;
        ::A1=1;
        ::A2=1;
        ::skip;
	  fi
	  now=now+1;
	od
}