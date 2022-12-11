import pyautogui
import time
import random
time.sleep(2)
score = 0
pause = 220, 870 
reset = 220, 965
bluematchload = 1500, 570
redmatchload = 1500, 670
retry = 990, 870
submit = 750, 870
while True:
    timetaken = 0

    pyautogui.moveTo(pause)
    pyautogui.click(pause)
    startTime = time.time()
    time.sleep(3)
    timetaken+=3


    pyautogui.moveTo(bluematchload)
    for clicks in range(5):
        pyautogui.click(bluematchload)
        clicksleep = 0.3
        time.sleep(clicksleep)
        timetaken+= clicksleep
    
    time.sleep(2)
    timetaken+=2
    pyautogui.moveTo(redmatchload)
    for clicks in range(5):
        pyautogui.click(redmatchload)
        clicksleep = 0.4
        time.sleep(clicksleep)
        timetaken+=clicksleep
            
    timetaken=time.time()-startTime
    timeleft = 60-timetaken
    pyautogui.moveTo(bluematchload)

    #DECREASE FOR LATER, INCREASE FOR EARLIER
    time.sleep(timeleft-(40.5))
    timetaken+=timeleft-(40.5)


    for clicks in range(2):
        pyautogui.click(bluematchload)
        time.sleep(0.2)
        timetaken+=0.2
    timetaken=time.time()-startTime
    timeleft = 60-timetaken
    pyautogui.moveTo(redmatchload)

    time.sleep(timeleft-(17))
    timetaken+=timeleft-timeleft-(17)


    for clicks in range(2):
        pyautogui.click(redmatchload)
        time.sleep(0.2)
        timetaken+=0.2
    timetaken=time.time()-startTime
    timeleft = 60-timetaken


    pyautogui.moveTo(pause)
    time.sleep(timeleft-(3.5))
    timetaken+=timeleft-(3.5)
    pyautogui.click(pause)
    time.sleep(4)
    pyautogui.moveTo(submit)
    time.sleep(0.1)
    pyautogui.click(submit)
    time.sleep(1.2)
    pyautogui.moveTo(retry)
    time.sleep(0.1)
    pyautogui.click(retry)
    time.sleep(5)




