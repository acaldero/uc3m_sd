
import os
import sys
import pickle
import random
import time


def chkpnt_save ( state ):
    try:
       with open("checkpoint.pickle", "wb") as outfile:
            pickle.dump(state, outfile)
       return 1
    except Exception as e:
       return -1

def chkpnt_load ( ):
    try:
        with open("checkpoint.pickle", "rb") as infile:
             state = pickle.load(infile)
        return state
    except Exception as e:
        return None

def chkpnt_remove():
    os.remove("checkpoint.pickle")
    return 1


#
# Main
#

# try to restart from last checkpoint...
state = chkpnt_load()
if state == None:
   state = {"iter": 0}

while state['iter'] < 50:
   # save checkpoint
   print('iter: ', state['iter'])
   chkpnt_save(state) 

   # processing that can fail...
   time.sleep(1)
   dice = random.randint(0,9)
   if (dice > 7):
       print('\U0001F9E8', '\U0001F9E8')
       sys.exit()

   # next iteration
   state['iter'] = state['iter'] + 1

# remove checkpoint
chkpnt_remove()

