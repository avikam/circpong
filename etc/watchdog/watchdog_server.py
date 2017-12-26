import subprocess
import SimpleHTTPServer
import SocketServer

PORT = 7898

class Handler(SimpleHTTPServer.SimpleHTTPRequestHandler):
    def do_GET(self):
        x = subprocess.Popen(['/home/pong/src/circpong/cirpong', 'config.ini'], cwd='/home/pong/src/circpong')
        resp = str(x.pid)

        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.send_header("Content-length", len(resp))
        self.end_headers()
        self.wfile.write(resp)

def main():
    while True:
        try:
            httpd = SocketServer.TCPServer(("127.0.0.1", PORT), Handler)
            print "serving at port", PORT
            httpd.serve_forever()
        except KeyboardInterrupt:
            return
        except:
            pass

main()
