//==============================================================
//   ____                                    _            _     
//  / __ \                                  | |          | |    
// | |  | | __      __   ___   ____   __ _  | |_    ___  | |__  
// | |  | | \ \ /\ / /  / _ \ |_  /  / _` | | __|  / __| | '_ \ 
// | |__| |  \ V  V /  |  __/  / /  | (_| | | |_  | (__  | | | |
//  \___\_\   \_/\_/    \___| /___|  \__,_|  \__|  \___| |_| |_|
//                                                              
//===== Nome ===================================================
//= Aedan, o Invocador de Chefes
//===== Descri��o ==============================================
//= Invocador de chefes bem simples. Seleciona monstros usando
//= n�meros como refer�ncia e os invoca em uma coordenada
//= aleat�ria do mapa. Apenas um chefe pode ser invocado por
//= minuto, para evitar spam. Se o player deslogar antes do fim
//= do timer, o NPC resetar� o timer para que o player n�o fique
//= preso em um trecho do c�digo.
//===== Mudan�as ===============================================
//= Formato: dia/m�s/ano - descri��o [autor] (vers�o)
//= 04/11/2018 - Lan�amento do script [Qwezatch] (1.0)
//==============================================================
mapa,x,y,4	script	Aedan	855,{
	set .@NPC_Name$,"^4CAF50[ Aedan ]^000000";
	// Armazena o "ID" dos MvPs em uma array para gerar a array de nomes e usar no comando monster
	setarray .@MvP_ID[1],1059,1647,1511,1651,1650,1785,1039,1873,1871,1086,1251,1389,1719,1731,1112,1115,1658,1157,1150,1159,1312,1885,1252,1832,1734,1779,1518,1688,1991,1646,1990,1147,1708,1648,1917,1956,1087,1038,1768,1623,1492,1373,1418,2022,1649,1583,1190,1751,1685;
	
	// Essa condi��o serve para evitar que players usem o NPC antes de um minuto se passar.
	if(getnpctimer(1) == 1){
		mes .@NPC_Name$;
		mes "Eu s� posso invocar um chefe por minuto. Por favor, espere um pouco mais.";
		close;
	}
	if(Aedan_First_Talk == 0){
		set Aedan_First_Talk,1;
		mes .@NPC_Name$;
		mes "Ol�, meu nome � Aedan. Se quiser, posso invocar um dos chefes do jogo para voc�. Estaria interessado?";
	} else {
		mes .@NPC_Name$;
		mes "Oh! Voc� por aqui novamente? Tudo bem, aposto que quer invocar mais alguns chefes, certo?";
	}
	next;
	if(select("Sim:N�o") == 2) goto End_Talk;
	
Choose_MvP:
	mes .@NPC_Name$;
	mes "Escolha um dos chefes na lista abaixo. Para invoc�-lo, digite o n�mero correspondente na caixa que ir� aparecer a seguir.";
	mes " ";
	// Cria uma array com o nome dos chefes e em seguida gera uma lista numerada
	for (set .@i,1; .@i < getarraysize(.@MvP_ID); set .@i,.@i+1){
		setarray .@MvP_Name$[.@i],strmobinfo(1,.@MvP_ID[.@i]);
		mes "^E53935"+.@i+".^000000 "+.@MvP_Name$[.@i];
	}
	next;
	if(select("Digitar:Cancelar") == 2) goto End_Talk;
	input .@MvP_Index;
	if(.@MvP_Index < 1 || .@MvP_Index > getarraysize(.@MvP_ID)-1) goto Invalid_Input;
	mes .@NPC_Name$;
	mes "Se prepare, "+.@MvP_Name$[.@MvP_Index]+" ser� invocado em instantes.";
	close2;
	attachnpctimer;
	initnpctimer;
	// Troque "mapa" pelo nome do mapa que deseja invocar os chefes (mantenha as aspas)
	// Se n�o quiser que os chefes spawnem aleatoriamente pelo mapa, troque 0,0 por outras coordenadas
	monster "mapa",0,0,.@MvP_Name$[.@MvP_Index],.@MvP_ID[.@MvP_Index],1;
	end;
	
OnTimer60000:
	stopnpctimer;
	// Avisa o player sobre o fim do timer
	dispbottom "Um minuto j� se passou. Agora voc� pode invocar mais chefes.";
	detachnpctimer;
	end;
	
Invalid_Input:
	mes .@NPC_Name$;
	mes "Parece que voc� n�o digitou um n�mero v�lido. Por favor, digite apenas um n�mero que esteja entre 1 e 49, tudo bem?";
	next;
	goto Choose_MvP;
	
End_Talk:
	mes .@NPC_Name$;
	mes "Tudo bem. Se precisar invocar chefes, � s� me procurar.";
	close;
}