import foos.config as config
import os
import time

from foos.process import call_and_log
from foos.platform import is_pi

class Plugin:
    def __init__(self, bus):
        self.bus = bus
        bus.subscribe_map({'replay_request': lambda d: self.replay('long', 'manual', {}),
                           'score_goal': lambda d: self.replay('short', 'goal', d)},
                          thread=True)

    def replay(self, replay_type, trigger, extra={}):
        extra['type'] = trigger
        if config.webcamPluginEn == True:
                config.webcamDev.stopRecord()
                os.rename(config.webcamRecFile, config.webcamReplayFile)
                config.webcamDev.startRecord(filename=config.webcamRecFile, fps=20.0)

        else:
            call_and_log(["video/generate-replay.sh", config.replay_path,
                str(config.ignore_recent_chunks),
                str(config.long_chunks), str(config.short_chunks)])
        self.bus.notify('replay_start', extra)

        if config.webcamPluginEn == True:
            config.webcamDev.runReplay(config.webcamReplayFile, 0.5, 3000)
        else:
            if is_pi():
                call_and_log(["video/replay.sh", os.path.join(config.replay_path, "replay_{}.h264".format(replay_type)), str(config.replay_fps)])
            else:
                time.sleep(3)

            
        self.bus.notify('replay_end')
