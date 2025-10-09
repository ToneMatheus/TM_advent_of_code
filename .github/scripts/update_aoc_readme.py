#!/usr/bin/env python3
import json, os, sys, urllib.request, datetime, re

AOC_YEAR = os.getenv("AOC_YEAR") or str(datetime.datetime.utcnow().year)
LEADERBOARD_ID = os.environ["AOC_LEADERBOARD_ID"]
SESSION = os.environ["AOC_SESSION"]
URL = f"https://adventofcode.com/{AOC_YEAR}/leaderboard/private/view/{LEADERBOARD_ID}.json"

def fetch_json(url, session):
    req = urllib.request.Request(url, headers={"Cookie": f"session={session}", "User-Agent": "github-action-aoc-progress"})
    with urllib.request.urlopen(req, timeout=20) as r:
        return json.loads(r.read().decode("utf-8"))

def build_grid(member):
    # Build a 25-day grid: ⭑⭑ (2 stars), ⭑ (1 star), ▢ (none)
    comp = member.get("completion_day_level", {})
    cells = []
    total_stars = 0
    for d in range(1, 26):
        day = str(d)
        if day in comp:
            parts = comp[day]
            stars = len(parts.keys())
            total_stars += stars
            cells.append("⭐⭐" if stars == 2 else "⭐")
        else:
            cells.append("▢")
    # Also provide a compact line with links to each day
    header = "| " + " | ".join([f"{d:02d}" for d in range(1, 26)]) + " |"
    sep    = "|" + "|".join(["---"]*25) + "|"
    row    = "| " + " | ".join(cells) + " |"
    return total_stars, "\n".join([header, sep, row])

def pick_self_member(data):
    # If the board has one member, it's you; otherwise pick the one with 'id' matching 'owner_id' if present
    members = data.get("members", {})
    if not members:
        raise RuntimeError("No members found in leaderboard JSON")
    if len(members) == 1:
        return next(iter(members.values()))
    owner_id = str(data.get("owner_id", ""))
    if owner_id and owner_id in members:
        return members[owner_id]
    # Fallback: highest local_score (often you)
    return max(members.values(), key=lambda m: m.get("local_score", 0))

def update_readme(block):
    path = "README.md"
    with open(path, "r", encoding="utf-8") as f:
        readme = f.read()
    new = re.sub(
        r"(<!-- AOC-START -->)(.*?)(<!-- AOC-END -->)",
        r"\n" + block + r"\n",
        readme,
        flags=re.DOTALL
    )
    if new != readme:
        with open(path, "w", encoding="utf-8") as f:
            f.write(new)
        return True
    return False

"""def main():
    data = fetch_json(URL, SESSION)
    me = pick_self_member(data)
    total_stars, table = build_grid(me)
    name = me.get("name") or f"User {me.get('id')}"
    last_ts = int(me.get("last_star_ts", 0))
    last_when = datetime.datetime.utcfromtimestamp(last_ts).strftime("%Y-%m-%d %H:%M UTC") if last_ts else "—"

    block = (
        f"**{AOC_YEAR} — {name}: {total_stars}⭐**  \n"
        f"_Last updated: {last_when}_\n\n"
        f"{table}\n\n"
        f"Legend: ⭐⭐ = both parts, ⭐ = part 1, ▢ = not done"
    )
    changed = update_readme(block)
    print("README updated." if changed else "No change.")
    # Exit nonzero if nothing changed? No—keep zero to avoid failing the workflow.
    sys.exit(0)"""

def render_year(year):
    url = f"https://adventofcode.com/{year}/leaderboard/private/view/{LEADERBOARD_ID}.json"
    data = fetch_json(url, SESSION)
    me = pick_self_member(data)
    total_stars, table = build_grid(me)
    name = me.get("name") or f"User {me.get('id')}"
    last_ts = int(me.get("last_star_ts", 0))
    last_when = datetime.datetime.utcfromtimestamp(last_ts).strftime("%Y-%m-%d %H:%M UTC") if last_ts else "—"
    return (
        f"**{year} — {name}: {total_stars}⭐**  \n"
        f"_Last updated: {last_when}_\n\n"
        f"{table}\n"
    )

def main():
    start_year = int(os.getenv("AOC_START_YEAR", 2024))
    end_year = int(os.getenv("AOC_YEAR") or datetime.datetime.utcnow().year)
    years = range(start_year, end_year + 1)

    parts = [render_year(y) for y in years]
    block = "\n".join(parts) + "\nLegend: ⭐⭐ = both parts, ⭐ = part 1, ▢ = not done"

    changed = update_readme(block)
    print("README updated." if changed else "No change.")
    sys.exit(0)

if __name__ == "__main__":
    main()
