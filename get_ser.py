import serial  
import time 

COM_PORT = 'COM5'    
BAUD_RATES = 9600    

ser = serial.Serial(COM_PORT, BAUD_RATES)   

start_time = None

try:
    while True:
        while ser.in_waiting:          
            ori_data = ser.readline()  
            data = ori_data.decode()   
            
            if int(data) == 0: start_time = time.time()
            if int(data) == 20:
                game_mode = ser.readline()  
                game_mode = game_mode.decode()
                curr_score = time.time() - start_time
                name = input('請輸入你的名字(長度小於10): ')
                
                
                while " " in name or "!" in name or ":" in name  or "," in name or "<" in name or ">" in name or len(name) > 10: 
                    print("給我重打不要亂塞符號")
                    name = input('請輸入你的名字: ')
                    
                get_num = f"Name: {name}, Score: !{curr_score:.3f}"
                
                
                score_arr = []
                score_arr.append(get_num)
                if "0" in game_mode:
                    with open("res_easy", "r", encoding='utf-8') as f:
                        for elem in f:
                            score_arr.append(elem.strip())
                    
                    mp = {}
                    for elem in score_arr:
                        mp[elem] = float(elem.split('!')[1])
                    
                    
                    place = [i for i in score_arr]
                    place.sort(key=lambda i: mp[i])
                    place = place[:10]
                    
                    with open("res_easy", "w", encoding='utf-8') as f:
                        for elem in place:
                            f.write(elem + "\n")
                elif "1" in game_mode:
                    with open("res_hard", "r", encoding='utf-8') as f:
                        for elem in f:
                            score_arr.append(elem.strip())
                    
                    mp = {}
                    for elem in score_arr:
                        mp[elem] = float(elem.split('!')[1])
                    
                    
                    place = [i for i in score_arr]
                    place.sort(key=lambda i: mp[i])
                    place = place[:10]
                    
                    with open("res_hard", "w", encoding='utf-8') as f:
                        for elem in place:
                            f.write(elem + "\n")
                
                    

except KeyboardInterrupt:
    ser.close()    
    print('離線')