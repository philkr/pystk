from subprocess import Popen, PIPE
from time import sleep, time

def main():
    track = {}
    track['train'] = ['cornfield_crossing', 'black_forest', 'snowmountain', 'fortmagma', 'olivermath', 'scotland',
                      'hacienda', 'abyss']
    track['test'] = ['volcano_island', 'zengarden', 'snowtuxpeak', 'lighthouse', 'minigolf']
    track['valid'] = ['candela_city', 'xr591', 'ravenbridge_mansion', 'sandtrack']

    commands = [('python3', 'dense_data.py', t, '-s', s, '-n', '500', '-k', '30', '-x', '%02d'%i) for i in range(10) for s in track for t in track[s]]
    # commands = [('python3', 'data.py', t, '-n', '100', '-k', '30', '-x', '%02d'%i) for i in range(5) for s in track for t in track[s]]
    print(commands)
    N_PARALLEL = 10
    running = []
    complete = 0
    t0 = time()
    for c in commands:
        while len(running) >= N_PARALLEL:
            sleep(1)
            still_running = []
            for r in running:
                if r.poll() is None:
                    still_running.append(r)
                else:
                    complete += 1
            running = still_running
            print('running = ', len(running), 'complete = ', complete, 'queued = ', len(commands) - len(running) - complete, 'time = ', int(time() - t0))
        running.append(Popen(c)) # ('bash', '-c', 'sleep 10')))#

    while len(running):
        sleep(1)
        still_running = []
        for r in running:
            if r.poll() is None:
                still_running.append(r)
        running = still_running
        print('running = ', len(running), 'complete = ', complete, 'queued = ', len(commands) - len(running) - complete, 'time = ', int(time() - t0))

    # for track_name in list_tracks:
    #     commands.extend()
    #     import os
    #     os.system('python3 data.py ' + trackName + ' -n 100 -k 30')


if __name__ == "__main__":
    main()